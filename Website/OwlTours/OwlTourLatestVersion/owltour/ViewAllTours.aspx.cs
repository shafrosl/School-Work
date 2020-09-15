using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class ViewAllTours : System.Web.UI.Page
    {
        static readonly string joinSuccess = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Booking has been made\");\n" +
         "location.href='ViewBookedTours.aspx';\n" +
         "</script>";

        static readonly string joineduser = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Hello! You have already joined this tour\");\n" +
         "</script>";

        static readonly string touristfound = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Hello! You're the tour guide\");\n" +
         "</script>";

        static readonly string oiWTF = "<script language=\"javascript\">\n" +
          "alert (\"Select a Search Criteria!\");\n" +
            "</script>";

        static readonly string loginFirstLaCb = "<script language=\"javascript\">\n" +
          "alert (\"Please Login to Join a Tour\");\n" +
            "</script>";

        static readonly string notTourist = "<script language=\"javascript\">\n" +
          "alert (\"You are not a tourist!\");\n" +
            "</script>";

        static readonly string joinedDate = "<script language=\"javascript\">\n" +
          "alert (\"You already have a booking on this date!\");\n" +
            "</script>";

        Bookings currBookings = new Bookings();

        protected void Page_Load(object sender, EventArgs e)
        {
            Join_Button.Visible = false;

            if ((string)Session["isLoggedIn"] != "Yes")
            {
                Session["userID"] = -1;
            }
        }

        protected void GridView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];

            if ((string)Session["isLoggedIn"] != "Yes" || currUser.getIsTourist() == "No")
            {
                if ((string)Session["isLoggedIn"] != "Yes")
                {
                    Type csType = this.GetType();
                    ClientScript.RegisterStartupScript(csType, "Error", loginFirstLaCb);
                }

                else
                {
                    Type csType = this.GetType();
                    ClientScript.RegisterStartupScript(csType, "Error", notTourist);
                }
            }

            else
            {
                Join_Button.Visible = true;
            }

        }

        protected void Join_Button_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            GridViewRow row = GridView1.SelectedRow;
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());

            string firstname = currUser.getFname();
            string lastname = currUser.getLname();
            string fullname = firstname + " " + lastname;

            currBookings.setb_TourID(int.Parse(row.Cells[0].Text));
            currBookings.setb_TourName(row.Cells[1].Text);
            currBookings.setb_TourDate(row.Cells[2].Text);
            currBookings.setb_TourArea(row.Cells[3].Text);
            currBookings.setb_TourLocation(row.Cells[4].Text);
            currBookings.setb_currentparti(int.Parse(row.Cells[5].Text));
            currBookings.setb_partinum(int.Parse(row.Cells[6].Text));
            currBookings.setb_tourdesc(row.Cells[7].Text);

            currBookings.setb_TourGuideID(int.Parse(row.Cells[8].Text));
            currBookings.setb_TourGuideName(row.Cells[9].Text);

            currBookings.setb_asTourist();
            currBookings.setbookername(fullname);
            currBookings.setb_userID(SessionID);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Bookings, Tours ";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            while (rdr.Read() == true)
            {
                if (SessionID == (Int32)rdr["b_userID"] && currBookings.Getb_TourID() == ((Int32)rdr["b_TourID"]))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", joineduser);
                    mDB.Close();
                    return;
                }

                if (fullname.Equals(currBookings.Getb_TourGuideName()))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", touristfound);
                    mDB.Close();
                    return;
                }

                if (SessionID == (Int32)rdr["b_userID"] && currBookings.Getb_TourDate() == (((DateTime)rdr["b_TourDate"]).ToString("dd/MMM/yyyy"))) 
                {
                    ClientScript.RegisterStartupScript(csType, "Error", joinedDate);
                    mDB.Close();
                    return;
                }
            }

            currBookings.InsertBooking(mDB, cmd, rdr);

            cmd.Dispose();
            rdr.Close();
            mDB.Close();
            GridView1.DataBind();
            ClientScript.RegisterStartupScript(csType, "Success", joinSuccess);
        }

        protected void BtnSearch_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            string query = searchBox.Text;
            string id;

            if ((string)Session["isLoggedIn"] == "Yes")
            {
                id = currUser.getUserID().ToString();
            }

            else
            {
                id = "-1";
            }

            if (searchBy.Text == "Tour Name")
            {
                if (full.Checked)
                {
                    SqlDataSource1.SelectCommand = "SELECT DISTINCT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [Parti_count], [T_Participants], [T_Desc], [userID], [TourGuideName] FROM [Tours] WHERE [TourDate] >= NOW() AND [userID] <> " + id + " AND [TourName] LIKE '%" + searchBox.Text + "%'";
                    GridView1.PageIndex = 0;
                    GridView1.EditIndex = -1;
                    GridView1.SelectedIndex = -1;
                    GridView1.DataBind();
                }

                else
                {
                    SqlDataSource1.SelectCommand = "SELECT DISTINCT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [Parti_count], [T_Participants], [T_Desc], [userID], [TourGuideName] FROM [Tours] WHERE [TourDate] >= NOW() AND [userID] <> " + id + " AND [Parti_count] < [T_Participants] AND [TourName] LIKE '%" + searchBox.Text + "%'";
                    GridView1.PageIndex = 0;
                    GridView1.EditIndex = -1;
                    GridView1.SelectedIndex = -1;
                    GridView1.DataBind();
                }

            }

            if (searchBy.Text == "Tour Guide")
            {
                if (full.Checked)
                {
                    SqlDataSource1.SelectCommand = "SELECT DISTINCT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [Parti_count], [T_Participants], [T_Desc], [userID], [TourGuideName] FROM [Tours] WHERE [TourDate] >= NOW() AND [userID] <> " + id + " AND [TourGuideName] LIKE '%" + searchBox.Text + "%'";
                    GridView1.PageIndex = 0;
                    GridView1.EditIndex = -1;
                    GridView1.SelectedIndex = -1;
                    GridView1.DataBind();
                }

                else
                {
                    SqlDataSource1.SelectCommand = "SELECT DISTINCT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [Parti_count], [T_Participants], [T_Desc], [userID], [TourGuideName] FROM [Tours] WHERE [TourDate] >= NOW() AND [userID] <> " + id + " AND [Parti_count] < [T_Participants] AND [TourGuideName] LIKE '%" + searchBox.Text + "%'";
                    GridView1.PageIndex = 0;
                    GridView1.EditIndex = -1;
                    GridView1.SelectedIndex = -1;
                    GridView1.DataBind();
                }
            }

            if (searchBy.Text == "Area")
            {
                if (full.Checked)
                {
                    SqlDataSource1.SelectCommand = "SELECT DISTINCT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [Parti_count], [T_Participants], [T_Desc], [userID], [TourGuideName] FROM [Tours] WHERE [TourDate] >= NOW() AND [userID] <> " + id + " AND [Area] LIKE '%" + searchBox.Text + "%'";
                    GridView1.PageIndex = 0;
                    GridView1.EditIndex = -1;
                    GridView1.SelectedIndex = -1;
                    GridView1.DataBind();
                }

                else
                {
                    SqlDataSource1.SelectCommand = "SELECT DISTINCT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [Parti_count], [T_Participants], [T_Desc], [userID], [TourGuideName] FROM [Tours] WHERE [TourDate] >= NOW() AND [userID] <> " + id + " AND [Parti_count] < [T_Participants] AND [Area] LIKE '%" + searchBox.Text + "%'";
                    GridView1.PageIndex = 0;
                    GridView1.EditIndex = -1;
                    GridView1.SelectedIndex = -1;
                    GridView1.DataBind();
                }
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