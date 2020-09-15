using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace owltour
{
    public partial class HomePage : System.Web.UI.Page
    {
        User currUser = new User();

        protected void Page_Load(object sender, EventArgs e)
        {
            if ((string)Session["isLoggedIn"] == "Yes")
            {
                currUser = (User)Session["currUser"];
            }

            if (((currUser.getIsAdmin()) == "Yes" || (currUser.getIsGuide()) == "Yes" || (currUser.getIsTourist()) == "Yes") && (currUser.getIsSuspended()) == "No")
            {
                welcomeMsg.Text = "Welcome back, " + (currUser.getFname()) + "!";
                susMsg.Visible = false;
            }

            if (((currUser.getIsAdmin()) == "Yes" || (currUser.getIsGuide()) == "Yes" || (currUser.getIsTourist()) == "Yes") && (currUser.getIsSuspended()) == "Yes")
            {
                welcomeMsg.Text = "Welcome back, " + (currUser.getFname()) + "!";
                susMsg.Text = "Your account has been banned. \nPlease contact admin.";
                susMsg.Visible = true;
            }
        }
    }
}