using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public class Tours
    {
            private int TourID;
            private string TourName;
            private string Tourdate;
            private string Tourarea;
            private string Tourlocation;
            private int particount;
            private string tourdesc;
            private int userID;
            private string isTourGuide;
            private string isTourist;
            private string TourGuideName;
            private string isjoined;


        //setting tour name
        public void setTourName(string TourName)
        {
            this.TourName = TourName;
        }
        //setting tourdate
        public void setTourdate(string Tourdate)
        {
            this.Tourdate = Tourdate;
        }
        //setting tourarea
        public void setTourArea(string Tourarea)
        {
            this.Tourarea = Tourarea;
        }
        //setting tourlocation
        public void setTourLocation(string Tourlocation)
        {
            this.Tourlocation = Tourlocation;
        }
        //setting participant count
        public void setPartiCount(int particount)
        {
            this.particount = particount;
        }
        //setting desc
        public void setDesc(string tourdesc)
        {
            this.tourdesc = tourdesc;
        }
        //setting the tourguide id
        public void setUserID(int userID)
        {
            this.userID = userID;
        }
        //setting that this is a tourguide
        public void setIsTourGuide()
        {
            this.isTourGuide = "Yes";
        }
        //setting if is tourist
        public void setIsTourist()
        {
            this.isTourist = "No";
        }
        //setting tourguidename
        public void setTourGuideName(string TourGuideName)
        {
            this.TourGuideName = TourGuideName;
        }
        //setting isJoined 
        public void setIsJoined()
        {
            this.isjoined = "Yes";
        }


        //getters
        public string getTourName()
        {
            return TourName;
        }

        public string getTourdate()
        {
            return Tourdate;
        }

        public string getTourArea()
        {
            return Tourarea;
        }

        public string getTourLocation()
        {
            return Tourlocation;
        }

        public int getparticount()
        {
            return particount;
        }

        public string getDesc()
        {
            return tourdesc;
        }

        public int getUserID()
        {
            return userID;
        }

        public string getisTourGuide()
        {
            return isTourGuide;
        }

        public string getisTourist()
        {
            return isTourist;
        }

        public string getTourGuideName()
        {
            return TourGuideName;
        }

        public string getisjoined()
        {
            return isjoined;
        }

        public string getIsTourist()
        {
            return isTourist;
        }

        public void insertTour(OleDbConnection mDB, OleDbCommand cmd, OleDbDataReader rdr) {

            // insert new record
            string strSQLInsert = "INSERT INTO "
                + " Tours  (TourName, TourDate, Area, T_MeetLoc, T_Participants, T_Desc, userID, asTourGuide, asTourist, TourGuideName, isJoined)"
                + " VALUES (@1,@2,@3,@4,@5,@6,@7,@8,@9,@10,@11)";

            cmd = new OleDbCommand(strSQLInsert, mDB);
            cmd.Parameters.AddWithValue("@1", getTourName());
            cmd.Parameters.AddWithValue("@2", getTourdate());
            cmd.Parameters.AddWithValue("@3", getTourArea());
            cmd.Parameters.AddWithValue("@4", getTourLocation());
            cmd.Parameters.AddWithValue("@5", getparticount());
            cmd.Parameters.AddWithValue("@6", getDesc());
            cmd.Parameters.AddWithValue("@7", getUserID());
            cmd.Parameters.AddWithValue("@8", getisTourGuide());
            cmd.Parameters.AddWithValue("@9", getIsTourist());
            cmd.Parameters.AddWithValue("@10", getTourGuideName());
            cmd.Parameters.AddWithValue("@11", getisjoined());

            cmd.ExecuteNonQuery();
            cmd.Dispose();

            rdr.Close();
            mDB.Close();
        }
    }
}