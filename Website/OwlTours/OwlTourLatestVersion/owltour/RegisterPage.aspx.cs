using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;
using System.Data;

namespace owltour
{
    public partial class RegisterPage : System.Web.UI.Page
    {
        static readonly string Error1 = //creating a dialogue box, give it a name
        "<script language=\"javascript\">\n" +
        "alert (\"Error - Please fill in all the blank la\");\n" +
        "</script>";

        static readonly string Success = //creating a dialogue box
        "<script language=\"javascript\">\n" +
        "alert (\"Your account has been succesfully created\");\n" +
            "location.href='Login.aspx';\n" +
        "</script>";

        static readonly string PasswordError = //creating a dialogue box
        "<script language=\"javascript\">\n" +
        "alert (\"Password and comfirm password doesn't match\");\n" +
        "</script>";

        static readonly string UsedUser = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Username has already been taken\");\n" +
         "</script>";

        static readonly string InvalidEmail = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Invalid email\");\n" +
         "</script>";

        static readonly string InvalidNumber = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Invalid Number. Please enter a 8 digit number starting with 9 or 8\");\n" +
         "</script>";

        static readonly string InvalidPassword = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Invalid Password, min length of 8\");\n" +
         "</script>";

        static readonly string CheckingBox = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error -Please select Tour Guide or Tourist\");\n" +
         "</script>";

        static readonly string UsedEmail = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Email has already been taken\");\n" +
         "</script>";

        System.Text.RegularExpressions.Regex phonepattern = new System.Text.RegularExpressions.Regex(@"[9|8][0-9]{7}");

        bool IsValidEmail(string email)
        {
            try
            {
                var addr = new System.Net.Mail.MailAddress(email);
                return addr.Address == email;
            }
            catch
            {
                return false;
            }
        }

        bool check = false;
        protected void Page_Load(object sender, EventArgs e)
        {


            if (IsPostBack)
            {
                rPassword.Attributes["value"] = rPassword.Text;
                rC_Password.Attributes["value"] = rC_Password.Text;
            }

            if (!IsPostBack)
            {
                LoadYears();
                LoadMonths();
            }

            if (rTourist.Checked == true || rGuide.Checked == true)
            {
                check = true;
            }

            else if (rTourist.Checked == false && rGuide.Checked == false)
            {
                check = false;
            }

        }

        private void LoadMonths()
        {
            DataSet dsMonths = new DataSet();
            dsMonths.ReadXml(Server.MapPath("~/DOBData/Months.xml"));

            DropDownList2.DataTextField = "Name";
            DropDownList2.DataValueField = "Number";

            DropDownList2.DataSource = dsMonths;
            DropDownList2.DataBind();
        }

        private void LoadYears()
        {
            DataSet dsYears = new DataSet();
            dsYears.ReadXml(Server.MapPath("~/DOBData/Years.xml"));

            DropDownList1.DataTextField = "Number";
            DropDownList1.DataValueField = "Number";

            DropDownList1.DataSource = dsYears;
            DropDownList1.DataBind();
        }

        protected void Register_Cancel_Click(object sender, EventArgs e)
        {

            Response.Redirect("HomePage.aspx", true);
        }

        //function when submit button is pressed.

        protected void Register_Submit_Click(object sender, EventArgs e)
        {
            User currUser = new User();

            string isTourist = rTourist.Checked ? "Yes" : "No";
            string isGuide = rGuide.Checked ? "Yes" : "No";

            currUser.setUsername(rUsername.Text);
            currUser.setPassword(rPassword.Text);
            currUser.setFname(rFName.Text);
            currUser.setLname(rLName.Text);
            currUser.setEmail(rEmail.Text);
            currUser.setAddress(rAdd.Text);
            currUser.setCNum(rCNum.Text);
            currUser.setDOB(Convert.ToDateTime(rDOB.Text));
            currUser.setIsTourist(isTourist);
            currUser.setIsGuide(isGuide);
            currUser.setIsAdmin("No");
            currUser.setIsSuspended("No");
            currUser.setRating(0);
            currUser.setRating_count(0);
            currUser.setAvgRating(0);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            Type csType = this.GetType();
            // check to ensure that UserId keyed in is not being in used by other Customers
            OleDbCommand cmd;
            OleDbDataReader rdr;
            string strSQLSelect = "SELECT * FROM Users ";
            cmd = new OleDbCommand(strSQLSelect, mDB);
            rdr = cmd.ExecuteReader();

            while (rdr.Read() == true)
            {
                //ensure no blank
                if (rUsername.Text == "" || rPassword.Text == "" || rC_Password.Text == "" || rFName.Text == ""
                    | rLName.Text == "" || rEmail.Text == "" || rAdd.Text == "" || rCNum.Text == ""
                    | rDOB.Text == "")
                {
                    ClientScript.RegisterStartupScript(csType, "Error", Error1);
                    return;
                }
                //ensure no dup username
                if (rUsername.Text.Equals((string)rdr["Username"]))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", UsedUser);
                    mDB.Close();
                    return;
                }
                //ensure no dup email
                if (rEmail.Text.Equals((string)rdr["Email"]))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", UsedEmail);
                    mDB.Close();
                    return;
                }
                //ensure password field == comfirm password field
                if (!rPassword.Text.Equals(rC_Password.Text))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", PasswordError);
                    return;
                }
                //ensure  email in string@sth.sth format
                if (IsValidEmail(rEmail.Text) == false)
                {
                    ClientScript.RegisterStartupScript(csType, "Error", InvalidEmail);
                    return;
                }
                //ensure phone in sg number format
                if (!phonepattern.IsMatch(rCNum.Text))
                {
                    ClientScript.RegisterStartupScript(csType, "Error", InvalidNumber);
                    return;
                }
                //make sure password at least length of 8
                if (rPassword.Text.Length < 8)
                {
                    ClientScript.RegisterStartupScript(csType, "Error", InvalidPassword);
                    return;
                }

                //ensure at least one checkbox is checked
                if (check == false)
                {
                    ClientScript.RegisterStartupScript(csType, "Error", CheckingBox);
                    return;
                }
            }

            currUser.InsertUser(mDB, cmd, rdr);

            ClientScript.RegisterStartupScript(csType, "Success", Success);
        }

        protected void DobCalender_SelectionChanged(object sender, EventArgs e)
        {
            string date = DobCalender.SelectedDate.ToString("dd/MMM/yyyy");
            rDOB.Text = date;
        }

        protected void DropDownList1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int year = Convert.ToInt16(DropDownList1.SelectedValue);
            int month = Convert.ToInt16(DropDownList2.SelectedValue);
            DobCalender.VisibleDate = new DateTime(year, month, 1);
            DobCalender.SelectedDate = new DateTime(year, month, 1);
        }

        protected void DropDownList2_SelectedIndexChanged(object sender, EventArgs e)
        {
            int year = Convert.ToInt16(DropDownList1.SelectedValue);
            int month = Convert.ToInt16(DropDownList2.SelectedValue);
            DobCalender.VisibleDate = new DateTime(year, month, 1);
            DobCalender.SelectedDate = new DateTime(year, month, 1);
        }
    }
}