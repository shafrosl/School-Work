<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="RegisterPage.aspx.cs" Inherits="owltour.RegisterPage" Debug="true"%>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="enterinfotable">
        Register an account with us!
        <br />
        <br />
            <table class="centertable">
                <col width ='150'>
                <col width ='300'>
                <tr>
                    <td>
                        Username
                    </td>
                    <td>
                        <asp:TextBox ID="rUsername" runat="server"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td>
                        Password
                    </td>
                    <td>
                        <asp:TextBox ID= "rPassword"  TextMode = "Password" runat="server"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td>
                        Confirm Password
                    </td>
                    <td>
                        <asp:TextBox ID="rC_Password" TextMode = "Password" runat="server"></asp:TextBox>
                    </td>
                </tr>   
                    <tr>
                    <td>
                        First Name
                    </td>
                    <td>
                        <asp:TextBox ID="rFName" runat="server" pattern="[A-Z'-]+[A-Za-z'-]{1,}" title="First name must start with uppercase letters followed by lowercase letters. Only alphanumeric and '- characters allowed. e.g. John"></asp:TextBox>
                    </td>
                </tr> 
                    <tr>
                    <td>
                        Last Name
                    </td>
                    <td>
                        <asp:TextBox ID="rLName" runat="server" pattern="[A-Z'-]+[A-Za-z'-]{1,}" title="Last name must start with uppercase letters followed by lowercase letters. Only alphanumeric and '- characters allowed. e.g. Wick"></asp:TextBox>
                    </td>
                </tr> 
                <tr>
                    <td>
                        E-Mail
                    </td>
                    <td>
                        <asp:TextBox ID="rEmail" runat="server" pattern="[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}$" title="Email must have characters followed by an @ sign, followed by more characters, and then a domain. e.g. OwlyTours@Hoot.com"></asp:TextBox>
                    </td>
                </tr> 
                <tr>
                    <td>
                        Address
                    </td>
                    <td>
                        <asp:TextBox ID="rAdd" runat="server" pattern="[A-Za-z0-9 -'@#&*()/]{1,}" Width="229px" title="Please fill up you address. Only alphanumeric and -'@#&*()/ characters allowed."></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td>
                        Contact Number
                    </td>
                    <td>
                        <asp:TextBox ID="rCNum" runat="server" pattern="[9|8][0-9]{7}" title="Please keep your phone number within 8 numbers. Must also start with 8/9. e.g. 98766851"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td>
                        Date of Birth
                    </td>
                    <td>
                        <asp:TextBox ID="rDOB" placeholder="DD/MM/YYYY" runat="server" Width="180px" ReadOnly="true"></asp:TextBox>
                            <br />
                        Month:&nbsp;&nbsp;&nbsp;
                            <asp:DropDownList ID="DropDownList2" runat="server" AutoPostBack="True" 
                                onselectedindexchanged="DropDownList2_SelectedIndexChanged">
                            </asp:DropDownList>
                        <br />
                        Year: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <asp:DropDownList ID="DropDownList1" runat="server" AutoPostBack="True" 
                                onselectedindexchanged="DropDownList1_SelectedIndexChanged">
                            </asp:DropDownList>   
                        <asp:Calendar ID="DobCalender" runat="server" Height="108px" Width="181px"  OnSelectionChanged="DobCalender_SelectionChanged"></asp:Calendar>
                    </td>
                </tr>
                <tr>
                    <td>
                        Registering as...
                    </td>
                    <td>
                        <asp:CheckBox ID="rTourist" runat="server" text="Tourist" />
                        <asp:CheckBox ID="rGuide" runat="server" text="Tour Guide" />
                    </td>
                </tr>
                <tr>
                <td style="height: 10px" ></td>
                </tr>
                <tr>
                    <td style="width: 160px"></td>
                    <td style="width: 80px">
                        <asp:Button ID="Register_Submit" runat="server" Text="Submit" OnClick="Register_Submit_Click" Width="70px"/>&nbsp;&nbsp;&nbsp;<asp:Button ID="Register_Cancel" runat="server" Text="Cancel" OnClick="Register_Cancel_Click" Width="70px" PostBackUrl="~/HomePage.aspx" UseSubmitBehavior="False" />
                    </td>
                </tr>
            </table>
            <br />
        </div>
</asp:Content>