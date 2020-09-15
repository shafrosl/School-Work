<%@ Page Language="C#"  MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="ProfilePage.aspx.cs" Inherits="owltour.ProfilePage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <br />
    <div class="enterinfotable">
        <table class="centertable">
            <col height='5'>
            <col width ='300'>
            <tr>
                <td style="width: 174px"><asp:Label ID="fName" runat="server"></asp:Label> <asp:Label ID="lName" runat="server"></asp:Label></td>
                <td class="auto-style1">@<asp:Label ID="username" runat="server"></asp:Label></td>
            </tr>
            <tr>
                <td style="width: 174px">Email:</td>
                <td class="auto-style1"><asp:Label ID="eMail" runat="server"></asp:Label></td>
            </tr> 
            <tr>
                <td style="width: 174px">Address:</td>
                <td class="auto-style1"><asp:Label ID="Address" runat="server"></asp:Label></td>
            </tr>
            <tr>
                <td style="width: 174px">Contact Number:</td>
                <td class="auto-style1"><asp:Label ID="cNum" runat="server"></asp:Label></td>
            </tr>
            <tr>
                <td style="width: 174px">Date of Birth:</td>
                <td class="auto-style1"><asp:Label ID="DOB" runat="server"></asp:Label></td>
            </tr>
            <tr>
                <td style="width: 174px"><asp:Label ID="RateH" runat="server" Text="Rating:"></asp:Label></td>
                <td class="auto-style1"><asp:Label ID="Rating" runat="server"></asp:Label></td>
            </tr>

            <tr>
                <td style="width: 174px">&nbsp;</td>
            </tr>
            <tr id="tRow" runat="server">
                <td style="width: 174px">
                    <asp:Label ID="isTourist" runat="server" Text="Owl Tourist"></asp:Label>
                </td>
            </tr>
            <tr id="gRow" runat="server">
                <td colspan ="2">
                    <asp:Label ID="isGuide" runat="server" Text="Official Owl Tour Guide "></asp:Label><asp:Label ID="ofLOL" runat="server" Text="of "></asp:Label><asp:Label ID="Area" runat="server"></asp:Label>
                </td>
            </tr>
            <tr id="aRow" runat="server">
                <td style="width: 174px">
                    <asp:Label ID="isAdmin" runat="server" Text="Official Owl Admin"></asp:Label>
                </td>
            </tr>
            <tr>
                <td style="height: 10px; width: 174px;" ></td>
            </tr>
            <tr>
                <td style="width: 174px"></td>
                <td style="width: 80px">
                    <asp:Button ID="EditProfile_btn" runat="server" Text="Edit" OnClick="EditProfile_btn_Click" Width="70px"/>&nbsp;&nbsp;&nbsp;<asp:Button ID="ProfileBack_btn" runat="server" Text="Back" OnClick="ProfileBack_btn_Click" Width="70px" />
                </td>
            </tr>
        </table>
    </div>
    <br />
</asp:Content>