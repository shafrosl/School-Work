using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;


namespace owltour
{
    public partial class CreateTour : System.Web.UI.Page
    {
        static readonly string blank = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Please fill in all the information\");\n" +
         "</script>";

        static readonly string invaliddate = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Please only choose valid dates\");\n" +
         "</script>";

        static readonly string tourOverlap = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - You already have a tour on the selected date\");\n" +
         "</script>";

        static readonly string createSuccess = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Tour has been created\");\n" +
         "location.href='ViewCreatedTours.aspx';\n" +
         "</script>";

        User currUser = new User();
        Tours currTour = new Tours();

        protected void Page_Load(object sender, EventArgs e)
        {
            if ((string)Session["isLoggedIn"] == "Yes")
            {
                currUser = (User)Session["currUser"];
            }
        }

        protected void SubmitTour_Click(object sender, EventArgs e)
        {
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());

            string firstname = Convert.ToString(currUser.getFname());
            string lastname = Convert.ToString(currUser.getLname());
            string name = firstname + " " + lastname;

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = @"SELECT * FROM Tours ";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            while (rdr.Read() == true)
            {
                if (TourName.Text == "" || T_showDate.Text == "" || T_Area.Text == "" || T_Location.Text == ""
                    || T_PartiCount.Text == "" || T_Desc.Text == "")
                {
                    ClientScript.RegisterStartupScript(csType, "Error", blank);
                    return;
                }

                //ensure no dup tour dates by same tour guide
                if ((T_Date.Text.Equals(rdr["TourDate"].ToString())) && (SessionID).Equals(Convert.ToString(rdr["userID"])))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", tourOverlap);
                    mDB.Close();
                    return;
                }

                if (T_PartiCount.Text == "Select Maximum No. of Tourists")
                {
                    ClientScript.RegisterStartupScript(csType, "Error", blank);
                    return;
                }
            }

            currTour.setTourName(TourName.Text);
            currTour.setTourdate(T_showDate.Text);
            currTour.setTourArea(T_Area.SelectedValue);
            currTour.setTourLocation(T_Location.Text);
            currTour.setPartiCount((int.Parse(T_PartiCount.SelectedValue)));
            currTour.setDesc(T_Desc.Text);
            currTour.setUserID(SessionID);
            currTour.setTourGuideName(name);
            currTour.setIsTourGuide();
            currTour.setIsTourist();
            currTour.setIsJoined();

            currTour.insertTour(mDB, cmd, rdr);

            ClientScript.RegisterStartupScript(csType, "Success", createSuccess);
        }

        protected void Cancel_cTour_Click(object sender, EventArgs e)
        {
            Response.Redirect("HomePage.aspx");
        }

        protected void T_Calender_SelectionChanged(object sender, EventArgs e)
        {
            DateTime date1 = T_Calender.SelectedDate;
            DateTime now = DateTime.Now;

            if (date1 < now)
            {
                T_showDate.Text = "";
                Type strType = this.GetType();
                ClientScript.RegisterStartupScript(strType, "Error", invaliddate);
            }

            else
            {
                T_Date.Text = date1.ToString("dd/MMM/yyyy hh:mm:ss tt");
                T_showDate.Text = date1.ToString("dd/MMM/yyyy");
            }
        }
    }
}