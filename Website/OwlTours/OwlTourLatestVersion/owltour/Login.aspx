<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="owltour.Login" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="enterinfotable">
        <p>Welcome to Owl Tours!</p>
            <table class="centertable">
                <col height='5'>
                <col width ='300'>
                <tr>
                    <td style="width: 90px">
                        Username: 
                    </td>
                    <td>
                        <asp:TextBox ID="Username" runat="server" OnTextChanged="TextBox1_TextChanged"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td style="width: 90px">
                        Password: 
                    </td>
                    <td>
                        <asp:TextBox ID="Password" TextMode="Password" runat="server"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                <td style="height: 10px" ></td>
                </tr>
                <tr>
                    <td style="width: 160px"></td>
                    <td style="width: 80px">
                        <asp:Button ID="LoginButton" runat="server" Text="Log in" OnClick="Login_Click" Width="70px"/>&nbsp;&nbsp;&nbsp;<asp:Button ID="RegisterButton" runat="server" OnClick="Register_Click" Text="Register" Width="70px" />
                    </td>
                </tr>
            </table>
            <br />
        </div>
</asp:Content>

