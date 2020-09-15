<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="CreateTour.aspx.cs" Inherits="owltour.CreateTour" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="enterinfotable"></div>
    <br />
    <div class="enterinfotable">
        <table class="centertable">
            <col height='5'>
            <col width ='500'>
            <tr>
                <td colspan="2">
                    <p style="font-size:25px"><b>Enter Tour Details</b></p>
                </td>
            </tr>
            <tr>
                <td style="width: 160px; height: 30px">
                    Name of Tour:
                </td>
                <td style="height: 30px">
                    <asp:TextBox ID="TourName" runat="server" Width="229px" pattern="[A-Z0-9'-@#*,()]+[A-Za-z0-9 '-@#*,()]{1,}" title="Tour name must start with uppercase letters followed by lowercase letters. Only alphanumeric and '-@#*,() characters allowed. e.g. Tour #2"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td style="width: 160px">
                    Date:
                </td>
                <td>
                    <asp:TextBox ID="T_showDate" runat="server" ReadOnly ="true" Width="229px"></asp:TextBox>
                    <asp:TextBox ID="T_Date" runat="server" Visible ="false" ReadOnly ="true" Width="229px"></asp:TextBox>
                    <br />
                    <asp:Calendar ID="T_Calender" runat="server" Height="108px" Width="130px" OnSelectionChanged="T_Calender_SelectionChanged"></asp:Calendar>
                    
                </td>
            </tr>

            <tr>
                <td style="width: 160px">
                    Area:
                </td>
                <td>
                    <asp:DropDownList ID="T_Area" runat="server" Width="229px">
                        <asp:ListItem Enabled="true" Text="Select Area"></asp:ListItem>
                        <asp:ListItem Text="Singapore" Value="Singapore"></asp:ListItem>
                        <asp:ListItem Text="Johore" Value="Johore"></asp:ListItem>
                        <asp:ListItem Text="Kuala Lumpur" Value ="Kuala Lumpur"></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td style="width: 160px">
                    Meeting Location:
                </td>
                <td>
                    <asp:TextBox ID="T_Location" runat="server" Width="229px" pattern="[A-Z0-9'-@#*()]+[A-Za-z0-9 '-@#*()]{1,}" title="Meeting Location must start with uppercase letters followed by lowercase letters. Only Alphanumeric and '-@#*() characters allowed. e.g. Your House"></asp:TextBox>
                </td>
            </tr>
                <tr>
                <td style="width: 160px">
                    Max Tourists:
                </td>
                <td>
                    <asp:DropDownList ID="T_PartiCount" runat="server" Width="229px">
                        <asp:ListItem Enabled="true" Text="Select Maximum No. of Tourists"></asp:ListItem>
                        <asp:ListItem Text="10" Value=10></asp:ListItem>
                        <asp:ListItem Text="15" Value=15></asp:ListItem>
                        <asp:ListItem Text="20" Value=20></asp:ListItem>
                        <asp:ListItem Text="25" Value=25></asp:ListItem>
                        <asp:ListItem Text="30" Value=30></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td style="width: 160px">
                    Description of Tour:
                </td>
                <td>
                   <asp:TextBox ID="T_Desc" runat="server" Width="250px" Height="120px" TextMode="MultiLine" AutoPostBack="false" pattern="[A-Za-z0-9 '-@#*,.()]{1,}" title="Description name must start with uppercase letters followed by lowercase letters. Only Alphanumeric and '-@#*,.() characters allowed."></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td style="width: 160px"></td>
                <td style="width: 80px">
                    <asp:Button ID="SubmitTour" runat="server" Text="Submit" OnClick="SubmitTour_Click" Width="70px" />&nbsp;&nbsp;&nbsp;<asp:Button ID="Cancel_cTour" runat="server" Text="Cancel" OnClick="Cancel_cTour_Click" Width="70px" UseSubmitBehavior="False" />
                </td>
            </tr>
        </table>
        <br />
    </div>   
</asp:Content>
