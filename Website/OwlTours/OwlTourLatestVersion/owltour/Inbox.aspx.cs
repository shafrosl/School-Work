using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class Inbox : System.Web.UI.Page
    {
        User currUser = new User();

        static readonly string searcherror =
            "<script language=\"javascript\">\n" +
            "alert (\"Select a Search Criteria!\");\n" +
            "location.href='Inbox.aspx'" +
            "</script>";

        static readonly string blank = //creating a dialogue box, give it a name
            "<script language=\"javascript\">\n" +
            "alert (\"Error - Please don't send an empty message!\");\n" +
            "location.href='Inbox.aspx'" +
            "</script>";

        protected void Page_Load(object sender, EventArgs e)
        {
            if ((string)Session["isLoggedIn"] == "Yes")
            {
                currUser = (User)Session["currUser"];
            }

            if ((bool)Session["Error"])
            {
                searchProfile.Visible = true;
                inboxView.Visible = false;
                inMsgDiv.Visible = false;
                outMsgDiv.Visible = false;
                searchUser.Visible = true;

            }

            else
            {
                inboxView.Visible = true;
                searchProfile.Visible = false;
                inMsgDiv.Visible = false;
                outMsgDiv.Visible = false;
                searchUser.Visible = false;
            }

            if (currUser.getIsSuspended() == "Yes")
            {
                sendMsgd.Visible = false;
                msgSpace.Visible = false;
            }

            // sets unread message to bold
            foreach (GridViewRow row in inboxView.Rows)
            {
                if ((row.Cells[3]).Text == "No")
                {
                    row.Font.Bold = true;
                }

                if ((row.Cells[3]).Text == "Yes")
                {
                    row.Font.Bold = false;
                }
            }
        }

        // when view message selected
        protected void GridView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            GridViewRow row = inboxView.SelectedRow;
            inboxView.DataBind();

            inboxView.Visible = true;
            searchProfile.Visible = false;
            inMsgDiv.Visible = true;
            outMsgDiv.Visible = false;
            searchUser.Visible = false;
            sendNewClick.Visible = false;

            if (currUser.getIsSuspended() == "Yes")
            {
                sendMsg.Visible = false;
                sendReplyClick.Enabled = false;
            }

            else
            {
                sendMsg.Visible = true;
                sendReplyClick.Enabled = true;
            }

            senderName.Text = "@" + row.Cells[1].Text;
            inMsg.Text = row.Cells[2].Text;
            Int32 msgID = Convert.ToInt32(row.Cells[4].Text);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();

            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Inbox";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            // insert new record
            string strSQLInsert = "UPDATE Inbox SET isRead = 'Yes' WHERE msgID = " + msgID;

            cmd = new OleDbCommand(strSQLInsert, mDB);

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();
        }

        // when send message selected
        protected void GridView2_SelectedIndexChanged(object sender, EventArgs e)
        {
            GridViewRow row = searchProfile.SelectedRow;

            inboxView.Visible = false;
            searchProfile.Visible = true;
            inMsgDiv.Visible = false;
            outMsgDiv.Visible = true;
            searchUser.Visible = true;
            sendReplyClick.Visible = false;
            rowReply.Visible = true;
            sendNewClick.Visible = true;
            recepientName.Text = "@" + row.Cells[1].Text;
        }

        // new message selected from sub-menu
        protected void send_Click(object sender, EventArgs e)
        {
            searchProfile.Visible = true;
            inboxView.Visible = false;
            inMsgDiv.Visible = false;
            outMsgDiv.Visible = false;
            searchUser.Visible = true;
        }

        // inbox selected from sub-menu
        protected void rec_Click(object sender, EventArgs e)
        {
            searchProfile.Visible = false;
            inboxView.Visible = true;
            inMsgDiv.Visible = false;
            outMsgDiv.Visible = false;
            searchUser.Visible = false;
        }

        // reply option clicked
        protected void reply_Click(object sender, EventArgs e)
        {
            inMsgDiv.Visible = true;
            outMsgDiv.Visible = true;
            rowReply.Visible = false;
            inboxReply.Visible = false;
            inboxReplySpace.Visible = false;
            sendNewClick.Visible = false;
            searchUser.Visible = false;
        }

        // delete option clicked
        protected void delete_Click(object sender, EventArgs e)
        {
            GridViewRow row = inboxView.SelectedRow;

            inboxView.Visible = true;
            searchProfile.Visible = false;
            inMsgDiv.Visible = false;
            outMsgDiv.Visible = false;
            searchUser.Visible = false;

            Int32 msgID = Convert.ToInt32(row.Cells[4].Text);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();

            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Inbox";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            // insert new record
            string strSQLInsert = "UPDATE Inbox SET isDeleted = 'Yes' WHERE msgID = " + msgID;

            cmd = new OleDbCommand(strSQLInsert, mDB);

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();

            inboxView.DataBind();
        }

        // when msg reply is sent
        protected void sendMsg_reply_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            GridViewRow row = inboxView.SelectedRow;
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());
            Int32 recepientsID = Convert.ToInt32(row.Cells[0].Text);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Inbox ";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            while (rdr.Read() == true)
            {
                // prevents empty msgs
                if (outMsg.Text == "")
                {
                    ClientScript.RegisterStartupScript(csType, "Error", blank);
                    return;
                }
            }

            // insert new record
            string strSQLInsert = "INSERT INTO "
                + " Inbox  (sendersID, recepientsID, message, isRead, isDeleted)"
                + " VALUES (@1,@2,@3,@4,@5)";

            cmd = new OleDbCommand(strSQLInsert, mDB);
            cmd.Parameters.AddWithValue("@1", SessionID);
            cmd.Parameters.AddWithValue("@2", recepientsID);
            cmd.Parameters.AddWithValue("@3", outMsg.Text);
            cmd.Parameters.AddWithValue("@4", "No");
            cmd.Parameters.AddWithValue("@5", "No");

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();

            Response.Redirect("Inbox.aspx");
        }

        // send new msg clicked
        protected void sendMsg_new_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            GridViewRow row = searchProfile.SelectedRow;
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());
            Int32 recepientsID = Convert.ToInt32(row.Cells[0].Text);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();

            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Inbox ";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            while (rdr.Read() == true)
            {
                // prevents empty msgs
                if (outMsg.Text == "")
                {
                    Session["Error"] = true;
                    ClientScript.RegisterStartupScript(csType, "Error", blank);
                    return;
                }
            }

            // insert new record
            string strSQLInsert = "INSERT INTO "
                + " Inbox  (sendersID, recepientsID, message, isRead, isDeleted)"
                + " VALUES (@1,@2,@3,@4,@5)";

            cmd = new OleDbCommand(strSQLInsert, mDB);
            cmd.Parameters.AddWithValue("@1", SessionID);
            cmd.Parameters.AddWithValue("@2", recepientsID);
            cmd.Parameters.AddWithValue("@3", outMsg.Text);
            cmd.Parameters.AddWithValue("@4", "No");
            cmd.Parameters.AddWithValue("@5", "No");

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();

            Response.Redirect("Inbox.aspx");
        }

        // search queries
        protected void BtnSearch_Click(object sender, EventArgs e)
        {
            string query = searchBox.Text;

            if (searchBy.Text == "Username")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [Username] LIKE '%" + searchBox.Text + "%'";
                searchProfile.PageIndex = 0;
                searchProfile.EditIndex = -1;
                searchProfile.SelectedIndex = -1;
                searchProfile.DataBind();

                searchProfile.Visible = true;
                inboxView.Visible = false;
                inMsgDiv.Visible = false;
                outMsgDiv.Visible = false;
                searchUser.Visible = true;
            }

            if (searchBy.Text == "First Name")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [firstName] LIKE '%" + searchBox.Text + "%'";
                searchProfile.PageIndex = 0;
                searchProfile.EditIndex = -1;
                searchProfile.SelectedIndex = -1;
                searchProfile.DataBind();

                searchProfile.Visible = true;
                inboxView.Visible = false;
                inMsgDiv.Visible = false;
                outMsgDiv.Visible = false;
                searchUser.Visible = true;
            }

            if (searchBy.Text == "Last Name")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [lastName] LIKE '%" + searchBox.Text + "%'";
                searchProfile.PageIndex = 0;
                searchProfile.EditIndex = -1;
                searchProfile.SelectedIndex = -1;
                searchProfile.DataBind();

                searchProfile.Visible = true;
                inboxView.Visible = false;
                inMsgDiv.Visible = false;
                outMsgDiv.Visible = false;
                searchUser.Visible = true;
            }

            if (searchBy.Text == "E-Mail")
            {
                SqlDataSource1.SelectCommand = "SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users] WHERE [Email] LIKE '%" + searchBox.Text + "%'";
                searchProfile.PageIndex = 0;
                searchProfile.EditIndex = -1;
                searchProfile.SelectedIndex = -1;
                searchProfile.DataBind();

                searchProfile.Visible = true;
                inboxView.Visible = false;
                inMsgDiv.Visible = false;
                outMsgDiv.Visible = false;
                searchUser.Visible = true;
            }

            if (searchBy.Text == "Select Search Criteria")
            {
                Type csType = this.GetType();
                Session["Error"] = true;
                ClientScript.RegisterStartupScript(csType, "Error", searcherror);
            }
        }

        protected void grdView1_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            searchProfile.Visible = false;
            inboxView.Visible = true;
            inMsgDiv.Visible = false;
            outMsgDiv.Visible = false;
            searchUser.Visible = false;

            inboxView.PageIndex = e.NewPageIndex;
            inboxView.DataBind();
        }

        protected void grdView2_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            searchProfile.Visible = true;
            inboxView.Visible = false;
            inMsgDiv.Visible = false;
            outMsgDiv.Visible = false;
            searchUser.Visible = true;

            inboxView.PageIndex = e.NewPageIndex;
            inboxView.DataBind();
        }
    }
}