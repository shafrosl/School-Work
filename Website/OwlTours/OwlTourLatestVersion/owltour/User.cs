using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.OleDb;

namespace owltour
{
    public class User
    {
        private int userID, rating, rating_count;
        private double avgRating;
        private string username, fname, lname, email, address, cNum, area, isTourist, isGuide, isAdmin, isSuspended, password;
        private DateTime dob;

        public void setUserID(int userID)
        {
            this.userID = userID;
        }

        public void setRating(int rating)
        {
            this.rating = rating;
        }

        public void setRating_count(int rating_count)
        {
            this.rating_count = rating_count;
        }

        public void setAvgRating(double avgRating)
        {
            this.avgRating = avgRating;
        }

        public void setUsername(string username)
        {
            this.username = username;
        }

        public void setFname(string fname)
        {
            this.fname = fname;
        }

        public void setLname(string lname)
        {
            this.lname = lname;
        }

        public void setEmail(string email)
        {
            this.email = email;
        }

        public void setAddress(string address)
        {
            this.address = address;
        }

        public void setArea(string area)
        {
            this.area = area;
        }

        public void setCNum(string cNum)
        {
            this.cNum = cNum;
        }

        public void setIsTourist(string isTourist)
        {
            this.isTourist = isTourist;
        }

        public void setIsGuide(string isGuide)
        {
            this.isGuide = isGuide;
        }

        public void setIsAdmin(string isAdmin)
        {
            this.isAdmin = isAdmin;
        }

        public void setIsSuspended(string isSuspended)
        {
            this.isSuspended = isSuspended;
        }

        public void setDOB(DateTime dob)
        {
            this.dob = dob;
        }

        public void setPassword(string password)
        {
            this.password = password;
        }
        public int getUserID()
        {
            return userID;
        }

        public int getRating()
        {
            return rating;
        }

        public int getRating_count()
        {
            return rating_count;
        }

        public double getAvgRating()
        {
            return avgRating;
        }

        public string getUsername()
        {
            return username;
        }

        public string getFname()
        {
            return fname;
        }

        public string getLname()
        {
            return lname;
        }

        public string getEmail()
        {
            return email;
        }

        public string getAddress()
        {
            return address;
        }

        public string getArea()
        {
            return area;
        }

        public string getCNum()
        {
            return cNum;
        }

        public string getIsTourist()
        {
            return isTourist;
        }

        public string getIsGuide()
        {
            return isGuide;
        }

        public string getIsAdmin()
        {
            return isAdmin;
        }

        public string getIsSuspended()
        {
            return isSuspended;
        }

        public DateTime getDOB()
        {
            return dob;
        }

        public string getPassword()
        {
            return password;
        }

        public void InsertUser(OleDbConnection mDB, OleDbCommand cmd, OleDbDataReader rdr)
        {

            string strSQLInsert = "INSERT INTO Users (Username, [Password], firstName, lastName, Email, Address, cNum, DOB, isTourist, isGuide, isAdmin, isSuspended) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)";

            cmd = new OleDbCommand(strSQLInsert, mDB);
            cmd.Parameters.AddWithValue("@Username", username);
            cmd.Parameters.AddWithValue("@Password", password);
            cmd.Parameters.AddWithValue("@firstName", fname);
            cmd.Parameters.AddWithValue("@lastName", lname);
            cmd.Parameters.AddWithValue("@Email", email);
            cmd.Parameters.AddWithValue("@Address", address);
            cmd.Parameters.AddWithValue("@cNum", cNum);
            cmd.Parameters.AddWithValue("@DOB", dob);
            cmd.Parameters.AddWithValue("@isTourist", isTourist);
            cmd.Parameters.AddWithValue("@isGuide", isGuide);
            cmd.Parameters.AddWithValue("@isAdmin", isAdmin);
            cmd.Parameters.AddWithValue("@isSuspended", isSuspended);

            cmd.ExecuteNonQuery();
            cmd.Dispose();
            mDB.Close();
        }
        public void UpdateProf(OleDbConnection mDB, OleDbCommand cmd, OleDbDataReader rdr,string textfieldname, string textfieldvalue)
        {
            String strSQL = @"UPDATE [Users] SET " + textfieldname +
            " = @newValue WHERE [userID] = " + userID;

            cmd = new OleDbCommand(strSQL, mDB);

            cmd.Parameters.AddWithValue("@newValue", OleDbType.Char).Value = textfieldvalue.ToString();
            cmd.ExecuteNonQuery();
            cmd.Dispose();
            mDB.Close();
        }
    }
}