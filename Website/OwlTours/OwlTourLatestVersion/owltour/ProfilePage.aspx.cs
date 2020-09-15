using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace owltour
{
    public partial class ProfilePage : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];

            username.Text = currUser.getUsername();
            fName.Text = currUser.getFname();
            lName.Text = currUser.getLname();
            eMail.Text = currUser.getEmail();
            Address.Text = currUser.getAddress();
            cNum.Text = currUser.getCNum();
            Area.Text = currUser.getArea();
            Rating.Text = Convert.ToDecimal(currUser.getAvgRating()).ToString("0.00");

            //DateTime dt = Convert.ToDateTime(Session["DOB"]).Date;
            DOB.Text = Convert.ToString(currUser.getDOB().ToShortDateString());

            if (currUser.getIsTourist() == "No")
            {
                isTourist.Visible = false;
                tRow.Visible = false;
            }

            if (currUser.getIsGuide() == "No")
            {
                isGuide.Visible = false;
                Area.Visible = false;
                ofLOL.Visible = false;
                Rating.Visible = false;
                RateH.Visible = false;
                gRow.Visible = false;
            }

            if (currUser.getIsAdmin() == "No")
            {
                isAdmin.Visible = false;
                aRow.Visible = false;
            }

            if (currUser.getArea() == "None Selected" || currUser.getArea() == "Select Area")
            {
                Area.Visible = false;
                ofLOL.Visible = false;
            }
        }

        protected void ProfileBack_btn_Click(object sender, EventArgs e)
        {
            Response.Redirect("HomePage.aspx");
        }

        protected void EditProfile_btn_Click(object sender, EventArgs e)
        {
            Response.Redirect("EditProfile.aspx");
        }
    }
}