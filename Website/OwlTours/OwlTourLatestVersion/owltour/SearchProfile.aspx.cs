using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class SearchProfile : System.Web.UI.Page
    {
        static readonly string susSuccess = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"User has been suspended\");\n" +
         "</script>";

        static readonly string unSusSuccess = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"User has been un-suspended\");\n" +
         "</script>";

        static readonly string oiWTF = "<script language=\"javascript\">\n" +
          "alert (\"Select a Search Criteria!\");\n" +
            "</script>";

        protected void Page_Load(object sender, EventArgs e)
        {
            susAcct.Visible = false;
            unSusAcct.Visible = false;
        }

        protected void GridView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            GridViewRow row = GridView1.SelectedRow;

            if (row.Cells[6].Text == "Yes")
                unSusAcct.Visible = true;

            else if (row.Cells[6].Text == "No")
                susAcct.Visible = true;
        }

        protected void susAcct_Click(object sender, EventArgs e)
        {
            GridViewRow row = GridView1.SelectedRow;
            Int32 SessionID = (Int32)Session["userID"];

            var tid = row.Cells[0].Text;

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;

            String strSql1 = @"SELECT * FROM Users where userID = " + tid;
            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();

            String strSQL = @"UPDATE [Users] SET isSuspended" +
             " = @newValue WHERE [userID] = " + tid;

            cmd = new OleDbCommand(strSQL, mDB);
            cmd.Parameters.AddWithValue("@newValue", OleDbType.Char).Value = "Yes";

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();
            GridView1.DataBind();
            ClientScript.RegisterStartupScript(csType, "Success", susSuccess);
        }

        protected void unSusAcct_Click(object sender, EventArgs e)
        {
            GridViewRow row = GridView1.SelectedRow;
            Int32 SessionID = (Int32)Session["userID"];

            var tid = row.Cells[0].Text;

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;

            String strSql1 = @"SELECT * FROM Users where userID = " + tid;
            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();

            String strSQL = @"UPDATE [Users] SET isSuspended" +
             " = @newValue WHERE [userID] = " + tid;

            cmd = new OleDbCommand(strSQL, mDB);
            cmd.Parameters.AddWithValue("@newValue", OleDbType.Char).Value = "No";

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();
            GridView1.DataBind();
            ClientScript.RegisterStartupScript(csType, "Success", unSusSuccess);
        }

        protected void BtnSearch_Click(object sender, EventArgs e)
        {
            string query = searchBox.Text;

            if (searchBy.Text == "Username")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [Username] LIKE '%" + searchBox.Text + "%'";
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }

            if (searchBy.Text == "First Name")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [firstName] LIKE '%" + searchBox.Text + "%'";
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }

            if (searchBy.Text == "Last Name")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [lastName] LIKE '%" + searchBox.Text + "%'";
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }

            if (searchBy.Text == "E-Mail")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [Email] LIKE '%" + searchBox.Text + "%'";
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }

            if (searchBy.Text == "Select Search Criteria")
            {
                Type csType = this.GetType();
                ClientScript.RegisterStartupScript(csType, "Error", oiWTF);
            }
        }

        protected void grdView_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            GridView1.PageIndex = e.NewPageIndex;
            GridView1.DataBind();
        }
    }
}