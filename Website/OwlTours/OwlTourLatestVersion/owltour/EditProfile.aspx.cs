using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class EditProfile : System.Web.UI.Page
    {
        static readonly string UpdateSuccess = "<script language=\"javascript\">\n" +
          "alert (\"Update Successful\");\n" +
            "location.href='ProfilePage.aspx';\n" +
            "</script>";

        static readonly string NoBlankLah = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Please fill up the information properly and leave no blanks.\");\n" +
         "</script>";

        static readonly string UsedEmail = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Email has already been taken\");\n" +
         "</script>";

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

        System.Text.RegularExpressions.Regex phonepattern = new System.Text.RegularExpressions.Regex(@"[9|8][0-9]{7}");

        protected void Page_Load(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];

            Int32 SessionID = Convert.ToInt32(currUser.getUserID());
            string isTour = "";
            string isGuide = "";
            

            if (!IsPostBack)
            {
                uFirstName.Text = currUser.getFname();
                uLastName.Text = currUser.getLname();
                uEmail.Text = currUser.getEmail();
                uAddress.Text = currUser.getAddress();
                uPhone.Text = currUser.getCNum();
                uArea.Text = currUser.getArea();
                isTour = currUser.getIsTourist();
                isGuide = currUser.getIsGuide();

              

                if (isTour == "Yes" && isGuide == "No")
                {
                    uRole.SelectedIndex = 1;
                    areaRow.Visible = false;
                }

                else if (isGuide == "Yes" && isTour == "No")
                {
                    uRole.SelectedIndex = 2;
                    areaRow.Visible = true;
                }
                else if (isGuide == "Yes" && isTour == "Yes")
                {
                    uRole.SelectedIndex = 3;
                    areaRow.Visible = true;
                }
            }

        
        }

        protected void EditProf_Submit_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            string curremail = currUser.getEmail();
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            OleDbCommand cmd;
            OleDbDataReader rdr;
            String strSql1 = @"SELECT * FROM Users";
            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();
            bool fnc = false;
            bool lnc = false;
            bool emc = false;
            bool adc = false;
            bool phc = false;
            bool arc = false;
            bool rlc = false;

            while (rdr.Read() == true)
            {
                //first name
                if (uFirstName.Text != "")
                {
                    fnc = false; 
                }
                else
                {
                    fnc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //for last name
                if (uLastName.Text != "")
                {
                    lnc = false; 
                }
                else
                {
                    lnc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //for email
                if (uEmail.Text != "" && IsValidEmail(uEmail.Text))
                {
                    emc = false;   
                }
                else
                {
                    emc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //ensure no dup email
                if (uEmail.Text.Equals((string)rdr["Email"]))
                {
                    if (uEmail.Text.Equals(curremail))
                    {
                        emc = false;
                    }
                    else
                    {
                        emc = true;
                        Type strType = this.GetType();
                        ClientScript.RegisterStartupScript(strType, "Error", UsedEmail);
                        mDB.Close();
                        return;
                    }
                }

                //for adddress
                if (uAddress.Text != "")
                {
                    adc = false;  
                }
                else
                {
                    adc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //for phone
                if (uPhone.Text != "")
                {
                    phc = false;
    
                }
                else
                {
                    phc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //for area
                if (uArea.SelectedIndex != -1)
                {
                    arc = false;     
                }
                else
                {
                    arc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //for updating whether still wanna be tourguide/tourist or both
                //for updating tourguide status
                if (uRole.SelectedIndex > 0)
                {
                    rlc = false;
                }
                        
                else
                {
                    rlc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }
            }

            if (!fnc && !lnc && !emc && !adc && !phc && !arc && !rlc)
            {
                String textfieldname1 = "firstName";
                String textfieldvalue1 = uFirstName.Text.ToString();
                UpdateProf(textfieldname1, textfieldvalue1);
                currUser.setFname(uFirstName.Text);

                textfieldname1 = "lastName";
                textfieldvalue1 = uLastName.Text.ToString();
                UpdateProf(textfieldname1, textfieldvalue1);
                currUser.setLname(uLastName.Text);

                textfieldname1 = "Email";
                textfieldvalue1 = uEmail.Text.ToString();
                UpdateProf(textfieldname1, textfieldvalue1);
                currUser.setEmail(uEmail.Text);

                textfieldname1 = "Address";
                textfieldvalue1 = uAddress.Text.ToString();
                UpdateProf(textfieldname1, textfieldvalue1);
                currUser.setAddress(uAddress.Text);

                textfieldname1 = "cNum";
                textfieldvalue1 = uPhone.Text.ToString();
                UpdateProf(textfieldname1, textfieldvalue1);
                currUser.setCNum(uPhone.Text);

                textfieldname1 = "Area";
                textfieldvalue1 = uArea.SelectedValue.ToString();
                UpdateProf(textfieldname1, textfieldvalue1);
                currUser.setArea(uArea.SelectedValue);

                if (uRole.SelectedIndex == 1)
                {
                    String textfieldname2 = "isTourist";
                    String textfieldvalue2 = "Yes";
                    UpdateProf(textfieldname2, textfieldvalue2);
                    currUser.setIsTourist("Yes");

                    String textfieldname3 = "isGuide";
                    String textfieldvalue3 = "No";
                    UpdateProf(textfieldname3, textfieldvalue3);
                    currUser.setIsGuide("No");
                }

                else if (uRole.SelectedIndex == 2)
                {
                    String textfieldname2 = "isTourist";
                    String textfieldvalue2 = "No";
                    UpdateProf(textfieldname2, textfieldvalue2);
                    currUser.setIsTourist("No");

                    String textfieldname3 = "isGuide";
                    String textfieldvalue3 = "Yes";
                    UpdateProf(textfieldname3, textfieldvalue3);
                    currUser.setIsGuide("Yes");
                }

                else if (uRole.SelectedIndex == 3)
                {
                    String textfieldname2 = "isTourist";
                    String textfieldvalue2 = "Yes";
                    UpdateProf(textfieldname2, textfieldvalue2);
                    currUser.setIsTourist("Yes");

                    String textfieldname3 = "isGuide";
                    String textfieldvalue3 = "Yes";
                    UpdateProf(textfieldname3, textfieldvalue3);
                    currUser.setIsGuide("Yes");
                }
            }

            mDB.Close();
            Session["currUser"] = currUser;
        }

        public void UpdateProf(string textfieldname, string textfieldvalue)
        {
            User currUser = (User)Session["currUser"];
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());

            currUser.setUserID(SessionID);

            Type csType = this.GetType();
            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            OleDbCommand cmd;
            OleDbDataReader rdr;
            String strSql1 = @"SELECT * FROM Users where userID = " + SessionID;
            cmd = new OleDbCommand(strSql1, mDB);

            rdr = cmd.ExecuteReader();

            currUser.UpdateProf(mDB, cmd, rdr, textfieldname, textfieldvalue);

            ClientScript.RegisterStartupScript(csType, "Success", UpdateSuccess);
        }

        protected void EditBack_Click(object sender, EventArgs e)
        {
            Response.Redirect("ProfilePage.aspx");
        }

        protected void updateRole_TextChanged(object sender, EventArgs e)
        {
            if (uRole.SelectedIndex <= 1)
            {
                areaRow.Visible = false;
            }

            else
            {
                areaRow.Visible = true;
            }
        }
    }
}