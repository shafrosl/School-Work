<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="EditProfile.aspx.cs" Inherits="owltour.EditProfile" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <br />
    <div class="enterinfotable">
        <table class="centertable">
            <col height='5'>
            <col width ='300'>
            <tr>
                <td colspan ="2">
                    <p style="font-size:25px"><b>Edit Profile</b></p>
                </td>
            </tr>
                <tr>
                    <td class="auto-style1">
                        First Name
                    </td>
                    <td>
                        <asp:TextBox ID= "uFirstName" runat="server" pattern="[A-Z'-]+[A-Za-z'-]{1,}" title="First name must start with uppercase letters followed by lowercase letters. Only alphanumeric and '- characters allowed. e.g. John" Width="229px" AutoPostBack="false"></asp:TextBox>
                    </td>
                </tr>

                <tr>
                    <td class="auto-style1">
                        Last Name
                    </td>
                    <td>
                        <asp:TextBox ID= "uLastName" runat="server" pattern="[A-Z'-]+[A-Za-z'-]{1,}" title="Last name must start with uppercase letters followed by lowercase letters. Only alphanumeric and '- characters allowed. e.g. Wick" Width="229px" AutoPostBack="false"></asp:TextBox>
                    </td>
                </tr>

                <tr>
                    <td class="auto-style1">
                        Email
                    </td>
                    <td>
                        <asp:TextBox ID= "uEmail" runat="server" pattern="[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}$" title="Email must have characters followed by an @ sign, followed by more characters, and then a domain. e.g. fuckyoula@21.co" Width="229px" AutoPostBack="false"></asp:TextBox>
                    </td>
                </tr>

                <tr>
                    <td class="auto-style1">
                        Address
                    </td>
                    <td>
                        <asp:TextBox ID= "uAddress" runat="server" pattern="[A-Za-z0-9 -'@#&*()/]{1,}" Width="229px" title="Please fill up you address. Only alphanumeric and -'@#&*()/ characters allowed." AutoPostBack="false"></asp:TextBox>
                    </td>
                </tr>

                <tr>
                    <td class="auto-style1">
                        Phone Number
                    </td>
                    <td>
                        <asp:TextBox ID= "uPhone" runat="server" pattern="[9|8][0-9]{7}" title="Please keep your phone number within 8 numbers. Must also start with 8/9. e.g. 98766851" Width="229px" AutoPostBack="false"></asp:TextBox>
                    </td>
                </tr>

            <tr>
                <td>
                    Role
                </td>
                <td>
                    <asp:DropDownList ID="uRole" runat="server" OnSelectedIndexChanged="updateRole_TextChanged" AutoPostBack="true" Width="229px">
                        <asp:ListItem Enabled="true" Text="Select Role"></asp:ListItem>
                        <asp:ListItem Text="Tourist" Value="Tourist"></asp:ListItem>
                        <asp:ListItem Text="Tour Guide" Value="Guide"></asp:ListItem>
                        <asp:ListItem Text="Both" Value="Both"></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>

            <tr id="areaRow" runat="server">
                <td>
                    Area
                </td>
                <td>
                    <asp:DropDownList ID="uArea" runat="server" Width="229px" AutoPostBack="true">
                        <asp:ListItem Enabled="true" Text="Select Area" Value="None Selected"></asp:ListItem>
                        <asp:ListItem Text="Singapore" Value="Singapore"></asp:ListItem>
                        <asp:ListItem Text="Johore" Value="Johore"></asp:ListItem>
                        <asp:ListItem Text="Kuala Lumpur" Value ="Kuala Lumpur"></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td style="height: 10px" ></td>
            </tr>
            <tr>
                <td style="width: 160px"></td>
                <td style="width: 80px">
                    <asp:Button ID="EditProf_Submit" runat="server" Text="Update" OnClick="EditProf_Submit_Click" Width="70px"/>&nbsp;&nbsp;&nbsp;<asp:Button ID="EditBack" runat="server" Text="Back" OnClick="EditBack_Click" Width="70px" />
                </td>
            </tr>
        </table>
    </div>
    <br />
</asp:Content>
