using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class Login : System.Web.UI.Page
    {
        static readonly string InvalidLogin = //creating a dialogue box, give it a name
        "<script language=\"javascript\">\n" +
        "alert (\"Error - Incorrect username or password\");\n" +
        "</script>";

        protected void Page_Load(object sender, EventArgs e)
        {
            Username.Visible = true;
            Password.Visible = true;
        }

        protected void Login_Click(object sender, EventArgs e)
        {
            User currUserLogin = new User();

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            OleDbCommand cmd;
            OleDbDataReader rdr;
            String strSql1 = @"SELECT * FROM Users";
            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();

            while (rdr.Read() == true)
            {
                if (Username.Text == (string)rdr["Username"] &&
                    Password.Text == (string)rdr["Password"])
                {
                    currUserLogin.setUserID(Convert.ToInt32(rdr["userID"]));
                    currUserLogin.setRating(Convert.ToInt32(rdr["rating"]));
                    currUserLogin.setRating_count(Convert.ToInt32(rdr["rating_count"]));
                    currUserLogin.setAvgRating(Convert.ToDouble(rdr["avgRating"]));

                    currUserLogin.setUsername(Convert.ToString(rdr["Username"]));
                    currUserLogin.setFname(Convert.ToString(rdr["firstName"]));
                    currUserLogin.setLname(Convert.ToString(rdr["lastName"]));
                    currUserLogin.setEmail(Convert.ToString(rdr["Email"]));
                    currUserLogin.setAddress(Convert.ToString(rdr["Address"]));
                    currUserLogin.setCNum(Convert.ToString(rdr["cNum"]));
                    currUserLogin.setArea(Convert.ToString(rdr["Area"]));
                    currUserLogin.setIsAdmin(Convert.ToString(rdr["isAdmin"]));
                    currUserLogin.setIsGuide(Convert.ToString(rdr["isGuide"]));
                    currUserLogin.setIsTourist(Convert.ToString(rdr["isTourist"]));
                    currUserLogin.setIsSuspended(Convert.ToString(rdr["isSuspended"]));

                    currUserLogin.setDOB(Convert.ToDateTime(rdr["DOB"]));

                    Session["userID"] = currUserLogin.getUserID();
                    Session["isLoggedIn"] = "Yes";
                    Session["Error"] = false;
                    Session["currUser"] = currUserLogin;
                    cmd.Dispose();
                    mDB.Close();
                    Response.Redirect("HomePage.aspx");
                }
                else
                {
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", InvalidLogin);
                }
            }
            cmd.Dispose();
        }

        protected void TextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        protected void Register_Click(object sender, EventArgs e)
        {
            Response.Redirect("RegisterPage.aspx");
        }
    }
}