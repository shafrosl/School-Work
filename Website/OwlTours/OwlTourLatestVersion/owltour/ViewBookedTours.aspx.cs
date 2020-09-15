using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class ViewBookedTours : System.Web.UI.Page
    {
        static readonly string deletesuccess = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Booking has been cancelled\");\n" +
         "</script>";

        static readonly string RateSuccess = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Rating has been updated\");\n" +
         "</script>";

        static readonly string invalidrating = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Please enter a rating\");\n" +
         "</script>";


        protected void Page_Load(object sender, EventArgs e)
        {
            cancelTour.Visible = false;
            RateDiv.Visible = false;
        }

        protected void GridView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            cancelTour.Visible = true;
        }

        protected void cancelTour_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            Bookings currBookings = new Bookings();

            GridViewRow row = GridView1.SelectedRow;

            Int32 SessionID = Convert.ToInt32(currUser.getUserID());

            var tid = row.Cells[0].Text;

            currBookings.setb_TourID(int.Parse(tid));
            currBookings.setb_userID(SessionID);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Bookings ";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            currBookings.DeleteBooking(mDB, cmd, rdr);

            GridView1.DataBind();
            ClientScript.RegisterStartupScript(csType, "Success", deletesuccess);
        }

        protected void GridView2_SelectedIndexChanged(object sender, EventArgs e)
        {
            RateDiv.Visible = true;
        }

        protected void Rate_Button_Click(object sender, EventArgs e)
        {
            GridViewRow row2 = GridView2.SelectedRow;
            var tourguideid = row2.Cells[3].Text;

         
            OleDbConnection mDB2 = new OleDbConnection();
            mDB2.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB2.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd2;
            OleDbDataReader rdr2;
            string strSQLSelect2 = "SELECT * FROM Users WHERE userID = " + tourguideid;
            cmd2 = new OleDbCommand(strSQLSelect2, mDB2);
            rdr2 = cmd2.ExecuteReader();

            // insert new record

            while (rdr2.Read() == true)
            {

                if (rating.Text == "Select Rating")
                {
                    ClientScript.RegisterStartupScript(csType, "Error", invalidrating);
                    mDB2.Close();
                    return;
                }

                else
                {
                    String textfieldname1 = "Rating";
                    Int32 textfieldvalue1 = Convert.ToInt32(rating.SelectedValue);
                    UpdateRating(textfieldname1, textfieldvalue1);
                }
            }

            // cmd2.ExecuteNonQuery();
            cmd2.Dispose();
            rdr2.Close();
            mDB2.Close();

            ClientScript.RegisterStartupScript(csType, "Success", RateSuccess);
        }

        public void UpdateRating(string textfieldname, Int32 textfieldvalue)
        {
            GridViewRow row2 = GridView2.SelectedRow;

            Bookings selectBookings = new Bookings();

           
            var tourguideid = row2.Cells[3].Text;
            var tourid = row2.Cells[0].Text;

            Int32 textfieldvalue1 = Convert.ToInt32(rating.SelectedValue);

            selectBookings.setb_TourGuideID(int.Parse(tourguideid));
            selectBookings.setb_TourID(int.Parse(tourid));

            Type csType = this.GetType();

            OleDbConnection mDB3 = new OleDbConnection();
            mDB3.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB3.Open();
            OleDbCommand cmd3;
            OleDbDataReader rdr3;
            String strSql1 = @"SELECT * FROM Users where userID = " + tourguideid;
            cmd3 = new OleDbCommand(strSql1, mDB3);
            rdr3 = cmd3.ExecuteReader();

            selectBookings.updateRating(mDB3, cmd3, rdr3, textfieldvalue1);

            GridView2.DataBind();
        }

        protected void grdView_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            GridView1.PageIndex = e.NewPageIndex;
            GridView1.DataBind();
        }
    }
}