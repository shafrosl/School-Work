using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class MasterPage : System.Web.UI.MasterPage
    {
        User currUser = new User();

        protected void Page_Load(object sender, EventArgs e)
        {
            if ((string)Session["isLoggedIn"] == "Yes")
            {
                currUser = (User)Session["currUser"];
            }

            if (Convert.ToString(currUser.getIsTourist()) != "Yes")
            {
                bookLink.Visible = false;
            }

            if (Convert.ToString(currUser.getIsGuide()) != "Yes")
            {
                createLink.Visible = false;
                tourLink.Visible = false;
            }

            if (Convert.ToString(currUser.getIsAdmin()) != "Yes")
            {
                searchLink.Visible = false;
            }

            if (Convert.ToString(currUser.getIsAdmin()) == null && Convert.ToString(currUser.getIsGuide()) == null && Convert.ToString(currUser.getIsTourist()) == null)
            {
                profileLink.Visible = false;
                logOut.Visible = false;
                inboxLink.Visible = false;
            }

            if (Convert.ToString(currUser.getIsAdmin()) == "Yes" || Convert.ToString(currUser.getIsGuide()) == "Yes" || Convert.ToString(currUser.getIsTourist()) == "Yes")
            {
                loginLink.Visible = false;
            }

            if ((string)Session["isLoggedIn"] == "Yes")
            {
                loginLink.Visible = false;
                registerLink.Visible = false;

                OleDbConnection mDB = new OleDbConnection();
                mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                     + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
                mDB.Open();
                OleDbCommand cmd;
                String strSql1 = @"SELECT COUNT(recepientsID) FROM Inbox WHERE isRead = 'No' AND recepientsID = " + Convert.ToInt32(currUser.getUserID());
                cmd = new OleDbCommand(strSql1, mDB);
                Session["inboxCount"] = (int)cmd.ExecuteScalar();

                cmd.Dispose();
                mDB.Close();
            }

            if (Convert.ToString(currUser.getIsSuspended()) == "Yes")
            {
                profileLink.Visible = false;
                searchLink.Visible = false;
                createLink.Visible = false;
                tourLink.Visible = false;
                bookLink.Visible = false;
                viewAllLink.Visible = false;
            }

            if (Convert.ToInt32(Session["inboxCount"]) > 0)
            {
                inboxLink.InnerText = "Inbox(" + Session["inboxCount"].ToString() + ")";
            }
        }

        protected void LogOut_Click(object sender, EventArgs e)
        {
            Session["currUser"] = null;
            Session["isLoggedIn"] = "No";

            Response.Redirect("HomePage.aspx");
        }
    }
}