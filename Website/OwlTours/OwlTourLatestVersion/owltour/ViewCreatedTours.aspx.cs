using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public partial class ViewCreatedTours : System.Web.UI.Page
    {
        // updates success
        static readonly string UpdateSuccess = "<script language=\"javascript\">\n" +
        "alert (\"Update Successful\");\n" +
         "location.href='ViewCreatedTours.aspx';\n" +
          "</script>";

        static readonly string NoBlankLah = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Oi got blank la noob\");\n" +
         "</script>";

        static readonly string invaliddate = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - Please pick dates after today\");\n" +
         "</script>";

        static readonly string tourOverlap = //creating a dialogue box, give it a name
         "<script language=\"javascript\">\n" +
         "alert (\"Error - You already have a tour on the selected date\");\n" +
         "</script>";

        Int32 t_id;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                TourName_Field.Visible = false;
                Date_Field.Visible = false;
                uT_Area.Visible = false;
                uT_MeetLoc.Visible = false;
                uT_PartiCount.Visible = false;
                uT_Desc.Visible = false;
                textcontain.Visible = false;
                GridView2.Visible = false;
            }
        }

        protected void GridView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            GridViewRow row = GridView1.SelectedRow;

            TourName_Field.Visible = true;
            Date_Field.Visible = true;
            uT_Area.Visible = true;
            uT_MeetLoc.Visible = true;
            uT_PartiCount.Visible = true;
            uT_Desc.Visible = true;
            textcontain.Visible = true;
            GridView2.Visible = true;

            TourName_Field.Text = row.Cells[1].Text;
            Date_Field.Text = row.Cells[3].Text;
            uT_Area.Text = row.Cells[4].Text;
            uT_MeetLoc.Text = row.Cells[5].Text;
            uT_Desc.Text = row.Cells[7].Text;

            if (Convert.ToInt32(row.Cells[6].Text) == 10)
            {
                uT_PartiCount.SelectedIndex = 1;
            }

            if (Convert.ToInt32(row.Cells[6].Text) == 15)
            {
                uT_PartiCount.SelectedIndex = 2;
            }

            if (Convert.ToInt32(row.Cells[6].Text) == 20)
            {
                uT_PartiCount.SelectedIndex = 3;
            }

            if (Convert.ToInt32(row.Cells[6].Text) == 25)
            {
                uT_PartiCount.SelectedIndex = 4;
            }

            if (Convert.ToInt32(row.Cells[6].Text) == 30)
            {
                uT_PartiCount.SelectedIndex = 5;
            }

            Int32 selecttour = Int32.Parse(row.Cells[0].Text);
            Session["selecttour"] = selecttour;
        }

        protected void TU_Cancel_Click(object sender, EventArgs e)
        {
            TourName_Field.Visible = false;
            Date_Field.Visible = false;
            uT_Area.Visible = false;
            uT_MeetLoc.Visible = false;
            uT_PartiCount.Visible = false;
            uT_Desc.Visible = false;
            textcontain.Visible = false;
            GridView2.Visible = false;
        }

        protected void TU_Update_Click(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());
            Type csType = this.GetType();
            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            OleDbCommand cmd;
            OleDbDataReader rdr;
            String strSql1 = @"SELECT * FROM Tours where userID = " + SessionID;

            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();
            bool tnc = false;
            bool dtc = false;
            bool arc = false;
            bool mlc = false;
            bool pcc = false;
            bool dec = false;

            while (rdr.Read() == true)
            {
                //tour name
                if (TourName_Field.Text != "")
                {
                    tnc = false;
                }
                else
                {
                    tnc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //date
                if (Date_Field.Text != "")
                {
                    dtc = false;
                }
                else
                {
                    dtc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //area
                if (uT_Area.SelectedIndex > 0)
                {
                    arc = false;
                }
                else
                {
                    arc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //meet loc
                if (uT_MeetLoc.Text != "")
                {
                    mlc = false;
                }
                else
                {
                    mlc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //participation count
                if (uT_PartiCount.SelectedIndex > 0)
                {
                    pcc = false;
                }
                else
                {
                    pcc = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                //description
                if (uT_Desc.Text != "")
                {
                    dec = false;
                }
                else
                {
                    dec = true;
                    Type strType = this.GetType();
                    ClientScript.RegisterStartupScript(strType, "Error", NoBlankLah);
                }

                if (!tnc && !dtc && !arc && !mlc && !pcc && !dec)
                {
                    String textfieldname1 = "TourName";
                    String textfieldvalue1 = TourName_Field.Text.ToString();
                    UpdateTour(textfieldname1, textfieldvalue1);

                    textfieldname1 = "TourDate";
                    textfieldvalue1 = Date_Field.Text.ToString();
                    UpdateTour(textfieldname1, textfieldvalue1);

                    textfieldname1 = "Area";
                    textfieldvalue1 = uT_Area.SelectedValue.ToString();
                    UpdateTour(textfieldname1, textfieldvalue1);

                    textfieldname1 = "T_MeetLoc";
                    textfieldvalue1 = uT_MeetLoc.Text.ToString();
                    UpdateTour(textfieldname1, textfieldvalue1);

                    textfieldname1 = "T_Participants";
                    textfieldvalue1 = uT_PartiCount.SelectedValue.ToString();
                    UpdateTour(textfieldname1, textfieldvalue1);

                    textfieldname1 = "T_Desc";
                    textfieldvalue1 = uT_Desc.Text.ToString();
                    UpdateTour(textfieldname1, textfieldvalue1);
                }
            }
            mDB.Close();
            GridView1.DataBind();
        }

        public void UpdateTour(string textfieldname, string textfieldvalue)
        {
            User currUser = (User)Session["currUser"];
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());
            Type csType = this.GetType();

            GridViewRow row = GridView1.SelectedRow;
            t_id = Int32.Parse(row.Cells[0].Text);

            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            OleDbCommand cmd;
            OleDbDataReader rdr;
            String strSql1 = @"SELECT * FROM Tours where userID = " + SessionID;
            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();

            String strSQL = @"UPDATE [Tours] SET " + textfieldname +
             " = @newValue WHERE [userID] = " + SessionID
             + "AND TourID = " + t_id;

            cmd = new OleDbCommand(strSQL, mDB);

            cmd.Parameters.AddWithValue("@newValue", OleDbType.Char).Value = textfieldvalue.ToString();
            cmd.ExecuteNonQuery();
            cmd.Dispose();
            mDB.Close();

            ClientScript.RegisterStartupScript(csType, "Success", UpdateSuccess);
        }

        protected void uTour_Cal_SelectionChanged(object sender, EventArgs e)
        {
            DateTime date = uTour_Cal.SelectedDate;
            DateTime now = DateTime.Now;

            if (date < now)
            {
                Date_Field.Text = "";
                Type strType = this.GetType();
                ClientScript.RegisterStartupScript(strType, "Error", invaliddate);
            }

            else
            {
                T_Date.Text = date.ToString("dd/MMM/yyyy hh:mm:ss tt");
                Date_Field.Text = date.ToString("dd/MMM/yyyy");
            }

            User currUser = (User)Session["currUser"];
            Int32 SessionID = Convert.ToInt32(currUser.getUserID());
            Type csType = this.GetType();
            OleDbConnection mDB = new OleDbConnection();
            mDB.ConnectionString = "Provider = Microsoft.ACE.OLEDB.12.0;Data source="
                 + Server.MapPath("~/App_Data/owlTourDatabase.accdb");
            mDB.Open();
            OleDbCommand cmd;
            OleDbDataReader rdr;
            String strSql1 = @"SELECT * FROM Tours where userID = " + SessionID;

            System.Diagnostics.Debug.WriteLine("SQL SEARCH");
            cmd = new OleDbCommand(strSql1, mDB);
            rdr = cmd.ExecuteReader();

            System.Diagnostics.Debug.WriteLine("EXECUTE");
            while (rdr.Read() == true)
            {
                //ensure no dup tour dates by same tour guide
                if ((T_Date.Text.Equals(rdr["TourDate"].ToString())))
                {
                    System.Diagnostics.Debug.WriteLine(rdr["TourDate"].ToString() + "   " + T_Date.Text);
                    ClientScript.RegisterStartupScript(csType, "Error", tourOverlap);
                    mDB.Close();
                    return;
                }
            }
            mDB.Close();
        }

        protected void GridView2_SelectedIndexChanged(object sender, EventArgs e)
        {
            GridView2.DataBind();
        }

        protected void tourTimeFrame_SelectedIndexChanged(object sender, EventArgs e)
        {
            User currUser = (User)Session["currUser"];
            if (tourTimeFrame.Text == "Upcoming")
            {
                SqlDataSource1.SelectCommand = "SELECT[TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [T_Participants], [T_Desc], [TourGuideName] FROM [Tours] WHERE [asTourGuide] = 'Yes' AND [userID] = " + currUser.getUserID().ToString() + " AND [TourDate] >= NOW()";
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }

            if (tourTimeFrame.Text == "Past")
            {
                SqlDataSource1.SelectCommand = "SELECT[TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [T_Participants], [T_Desc], [TourGuideName] FROM [Tours] WHERE [asTourGuide] = 'Yes' AND [userID] = " + currUser.getUserID().ToString() + " AND [TourDate] < NOW()";
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }

            if (tourTimeFrame.Text == "All")
            {

                SqlDataSource1.SelectCommand = "SELECT[TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [T_Participants], [T_Desc], [TourGuideName] FROM [Tours] WHERE [asTourGuide] = 'Yes' AND [userID] = " + currUser.getUserID().ToString();
                GridView1.PageIndex = 0;
                GridView1.EditIndex = -1;
                GridView1.SelectedIndex = -1;
                GridView1.DataBind();
            }
        }

        protected void grdView1_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            GridView1.PageIndex = e.NewPageIndex;
            GridView1.DataBind();
        }

        protected void grdView2_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            GridView2.PageIndex = e.NewPageIndex;
            GridView2.DataBind();
        }
    }
}