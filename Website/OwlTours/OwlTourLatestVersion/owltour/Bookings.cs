using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public class Bookings
    {

            private int b_TourID;
            private string b_TourName;
            private int b_userID;
            private string b_TourDate;
            private string b_TourArea;
            private string b_TourLocation;
            private int b_currentparti;
            private int b_partinum;
            private string b_tourdesc;
            private int b_TourGuideID;
            private string b_TourGuideName;
            private string bookername;
            private string asTourist;

        //setters
        //setting tour id
        public void setb_TourID(int b_TourID)
        {
            this.b_TourID = b_TourID;
        }
        //setting tour name
        public void setb_TourName(string b_TourName)
        {
            this.b_TourName = b_TourName;
        }
        //setting b user id
        public void setb_userID(int b_userID)
        {
            this.b_userID = b_userID;
        }
        //setting tour date
        public void setb_TourDate(string b_TourDate)
        {
            this.b_TourDate = b_TourDate;
        }
        //setting tourlocation
        public void setb_TourLocation(string b_TourLocation)
        {
            this.b_TourLocation = b_TourLocation;
        }
        //setting participant current count
        public void setb_currentparti(int b_currentparti)
        {
            this.b_currentparti = b_currentparti;
        }
        //setting max parti num
        public void setb_partinum(int b_partinum)
        {
            this.b_partinum = b_partinum;
        }
        //setting the tour desc
        public void setb_tourdesc(string b_tourdesc)
        {
            this.b_tourdesc = b_tourdesc;
        }
        //setting the tour guide id
        public void setb_TourGuideID(int b_TourGuideID)
        {
            this.b_TourGuideID = b_TourGuideID;
        }
        //setting tour guide name
        public void setb_TourGuideName(string b_TourGuideName)
        {
            this.b_TourGuideName = b_TourGuideName;
        }

        //setting tour area
        public void setb_TourArea(string b_TourArea)
        {
            this.b_TourArea = b_TourArea;
        }

        //setting tour id
        public void setbookername(string bookername)
        {
            this.bookername = bookername;
        }
        //setting tour name
        public void setb_asTourist()
        {
            this.asTourist = "Yes";
        }

        //getters
        public int Getb_TourID()
        {
            return b_TourID;
        }

        public string Getb_TourName()
        {
            return b_TourName;
        }

        public string Getb_TourDate()
        {
            return b_TourDate;
        }

        public string Getb_TourArea()
        {
            return b_TourArea;
        }

        public string Getb_TourLocation()
        {
            return b_TourLocation;
        }

        public int Getb_currentparti()
        {
            return b_currentparti;
        }

        public int getb_partinum()
        {
            return b_partinum;
        }

        public string Getb_tourdesc()
        {
            return b_tourdesc;
        }

        public int Getb_TourGuideID()
        {
            return b_TourGuideID;
        }

        public string Getb_TourGuideName()
        {
            return b_TourGuideName;
        }

        public string getb_TourArea()
        {
            return b_TourArea;
        }

        public string getbookername()
        {
            return bookername;
        }

        public string getAsTourist()
        {
            return asTourist = "Yes";
        }

        public int getb_userID()
        {
            return b_userID;
        }
        public void InsertBooking(OleDbConnection mDB, OleDbCommand cmd, OleDbDataReader rdr ) {


        // insert new record
        string strSQLInsert = "INSERT INTO "
                + " Bookings  (b_TourID, b_userID, b_Name, b_TourName, b_TourDate, b_Area, b_MeetLoc, b_Desc, b_asTourist, b_GuideName, b_TourGuideID)"
                + " VALUES (@1,@2,@3,@4,@5,@6,@7,@8,@9,@10,@11)";

            cmd = new OleDbCommand(strSQLInsert, mDB);
            cmd.Parameters.AddWithValue("@1", Getb_TourID());
            cmd.Parameters.AddWithValue("@2", getb_userID());
            cmd.Parameters.AddWithValue("@3", getbookername());
            cmd.Parameters.AddWithValue("@4", Getb_TourName());
            cmd.Parameters.AddWithValue("@5", Getb_TourDate());
            cmd.Parameters.AddWithValue("@6", getb_TourArea());
            cmd.Parameters.AddWithValue("@7", Getb_TourLocation());
            cmd.Parameters.AddWithValue("@8", Getb_tourdesc());
            cmd.Parameters.AddWithValue("@9", getAsTourist());
            cmd.Parameters.AddWithValue("@10", Getb_TourGuideName());
            cmd.Parameters.AddWithValue("@11", Getb_TourGuideID());

            cmd.ExecuteNonQuery();

            //============ for updating participation count
            String strSQLupdate = @"UPDATE [Tours] SET Parti_count = (Parti_Count + 1) WHERE TourID = " + Getb_TourID();
            cmd = new OleDbCommand(strSQLupdate, mDB);
            cmd.ExecuteNonQuery();
            //==============================================================

            cmd.Dispose();
            rdr.Close();
            mDB.Close();
        }

        public void DeleteBooking(OleDbConnection mDB, OleDbCommand cmd, OleDbDataReader rdr)
        {


            // insert new record
            string strSQLInsert = "DELETE FROM "
                + " Bookings WHERE b_TourID = @1 AND b_userID = @2";

            cmd = new OleDbCommand(strSQLInsert, mDB);
            cmd.Parameters.AddWithValue("@1", b_TourID);
            cmd.Parameters.AddWithValue("@2", b_userID);

            cmd.ExecuteNonQuery();

            // insert new record
            String strSQLupdate = @"UPDATE [Tours] SET Parti_count = (Parti_Count - 1) WHERE TourID = " + b_TourID;
            cmd = new OleDbCommand(strSQLupdate, mDB);
            cmd.ExecuteNonQuery();
            cmd.Dispose();
            rdr.Close();
            mDB.Close();
        }

        public void updateRating(OleDbConnection mDB3, OleDbCommand cmd3, OleDbDataReader rdr3, Int32 selectedRating)
        {
             string textfieldname = "Rating";
            String strSQL = @"UPDATE [Users] SET " + textfieldname +
             " = (@newValue + Rating), [Rating_Count] = (Rating_Count + 1) WHERE [userID] = " + b_TourGuideID;

            cmd3 = new OleDbCommand(strSQL, mDB3);

            cmd3.Parameters.AddWithValue("@newValue", OleDbType.Char).Value = selectedRating.ToString();

            cmd3.ExecuteNonQuery();
            cmd3.Dispose();

            // insert new record
            string strSQL2 = "DELETE FROM "
                + " Bookings WHERE b_TourGuideID = @1 AND b_TourID = @2";

            cmd3 = new OleDbCommand(strSQL2, mDB3);
            cmd3.Parameters.AddWithValue("@1", b_TourGuideID);
            cmd3.Parameters.AddWithValue("@2", b_TourID);

            cmd3.ExecuteNonQuery();
            cmd3.Dispose();

            mDB3.Close();
        }
    }
}