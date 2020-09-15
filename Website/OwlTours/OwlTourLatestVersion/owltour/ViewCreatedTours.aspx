<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="ViewCreatedTours.aspx.cs" Inherits="owltour.ViewCreatedTours"  Debug="true"%>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="gridPad">
        <br />
    <asp:Label ID="conText" runat="server">Your Hosted Tours</asp:Label>
    <br/>
    <br/>
    <asp:DropDownList ID="tourTimeFrame" runat="server" AutoPostBack="true" OnSelectedIndexChanged="tourTimeFrame_SelectedIndexChanged" Width="130px">
        <asp:ListItem Text="Upcoming"></asp:ListItem>
        <asp:ListItem Text="Past"></asp:ListItem>
        <asp:ListItem Text="All"></asp:ListItem>
    </asp:DropDownList>
    <br />
    <br />
    <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataKeyNames="TourID" DataSourceID="SqlDataSource1" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView1_SelectedIndexChanged" Width="80%" AllowSorting="True" OnPageIndexChanging="grdView1_PageIndexChanging" AllowPaging="true" PageSize="10">
        <AlternatingRowStyle BackColor="#e7eded" />
        <EmptyDataTemplate>No tours found. Go create one!</EmptyDataTemplate>
        <Columns>
            <asp:BoundField DataField="TourID" HeaderText="#" InsertVisible="False" ReadOnly="True" SortExpression="TourID" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Right" /></asp:BoundField>
            <asp:BoundField DataField="TourName" HeaderText="Tour Name" SortExpression="TourName" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="TourGuideName" HeaderText="Tour Guide Name" SortExpression="TourGuideName" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="TourDate" HeaderText="Date" SortExpression="TourDate" ItemStyle-Width="100px" DataFormatString="{0:d}" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="Area" HeaderText="Area" SortExpression="Area" ItemStyle-Width="80px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="T_MeetLoc" HeaderText="Meet-Up Loc" SortExpression="T_MeetLoc" ItemStyle-Width="80px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="T_Participants" HeaderText="Max. Tourists" SortExpression="T_Participants" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="T_Desc" HeaderText="Description" SortExpression="T_Desc" ItemStyle-Width="200px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Left" /></asp:BoundField>
            <asp:CommandField SelectText="Edit/View" ShowSelectButton="True" ItemStyle-HorizontalAlign="Center" ItemStyle-Font-Size="Smaller" ItemStyle-Width="50px" />
        </Columns>
        <FooterStyle BackColor="#334144" />
        <HeaderStyle BackColor="#334144" ForeColor="GhostWhite" Font-Underline="False" Font-Bold="True" Font-Size="Small" HorizontalAlign="Center"/>
        <PagerStyle BackColor="#c7d6d6" ForeColor="DarkSlateGray" HorizontalAlign="Center" />
        <SelectedRowStyle BackColor="DarkSlateGray" ForeColor="GhostWhite" />
        <SortedAscendingCellStyle BackColor="#FAFAE7" />
        <SortedAscendingHeaderStyle BackColor="#DAC09E" />
        <SortedDescendingCellStyle BackColor="#E1DB9C" />
        <SortedDescendingHeaderStyle BackColor="#C2A47B" />
    </asp:GridView>
    <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString %>" ProviderName="<%$ ConnectionStrings:ConnectionString.ProviderName %>" SelectCommand="SELECT [TourID], [TourName], [TourDate], [Area], [T_MeetLoc], [T_Participants], [T_Desc], [TourGuideName] FROM [Tours] WHERE (([asTourGuide] = ?) AND ([userID] = ?) AND TourDate  &gt;= NOW()) ORDER BY TourDate">
        <SelectParameters>
            <asp:Parameter DefaultValue="Yes" Name="asTourGuide" Type="String" />
            <asp:SessionParameter Name="userID" SessionField="userID" Type="Int16" />
        </SelectParameters>
    </asp:SqlDataSource>
    <br />
    </div>

    <div class="gridPad">
        <asp:GridView ID="GridView2" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataSourceID="SqlDataSource2" ForeColor="Black" GridLines="None" Width="40%" AllowSorting="True" OnPageIndexChanging="grdView2_PageIndexChanging" AllowPaging="true" PageSize="10">
        <AlternatingRowStyle BackColor="#e7eded" />
            <EmptyDataTemplate>Nobody seems interested in joining. (Maybe they don't like you)</EmptyDataTemplate>
            <Columns>
                <asp:BoundField DataField="b_Name" HeaderText="Participants" SortExpression="b_Name" ItemStyle-HorizontalAlign="Center" ItemStyle-Font-Size="Smaller"/>
            </Columns>
            <FooterStyle BackColor="#334144" />
        <HeaderStyle BackColor="#334144" ForeColor="GhostWhite" Font-Underline="False" Font-Bold="True" Font-Size="Small" HorizontalAlign="Center"/>
        <PagerStyle BackColor="#c7d6d6" ForeColor="DarkSlateGray" HorizontalAlign="Center" />
        <SelectedRowStyle BackColor="DarkSlateGray" ForeColor="GhostWhite" />
            <SortedAscendingCellStyle BackColor="#FAFAE7" />
            <SortedAscendingHeaderStyle BackColor="#DAC09E" />
            <SortedDescendingCellStyle BackColor="#E1DB9C" />
            <SortedDescendingHeaderStyle BackColor="#C2A47B" />
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource2" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString4 %>" ProviderName="<%$ ConnectionStrings:ConnectionString4.ProviderName %>" SelectCommand="SELECT [b_Name] FROM [Bookings] WHERE [b_TourID] = ?">
            <SelectParameters>
                <asp:SessionParameter DefaultValue="" Name="?" SessionField="selecttour" />
            </SelectParameters>
        </asp:SqlDataSource>
    </div>
    <br />


    <div class="enterinfotable" id ="textcontain" runat="server">
        <br />
        <br />
        <table class="centertable">
            <col height='5'>
            <col width ='300'>
            <tr>
                <td colspan ="2">
                    <p style="font-size:25px"><b>Edit the Selected Tour</b></p>
                </td>
            </tr>
            <tr>
                <td>
                    Tour Name:
                </td>
                <td>
                    <asp:TextBox ID="TourName_Field" runat="server" pattern="[A-Z0-9'-@#*()]+[A-Za-z0-9 '-@#*,()]{1,}" title="Tour name must start with uppercase letters followed by lowercase letters. Only alphanumeric and '-@#*,() characters allowed. e.g. Tour #2" AutoPostBack="false"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td>
                    Date:
                </td>
                <td>
                    <asp:TextBox ID="Date_Field" runat="server" ReadOnly="true" AutoPostBack="false"></asp:TextBox>
                    <asp:TextBox ID="T_Date" runat="server" Visible="false" ReadOnly="true" AutoPostBack="false"></asp:TextBox>
                    <br />
                    <asp:Calendar ID="uTour_Cal" runat="server" OnSelectionChanged="uTour_Cal_SelectionChanged" AutoPostBack="false"></asp:Calendar>
                </td>
            </tr>
            <tr>
                <td>
                    Area:
                </td>
                <td>
                    <asp:DropDownList ID="uT_Area" runat="server" Width="165px" AutoPostBack="false">
                        <asp:ListItem Enabled="true" Text="Select Area"></asp:ListItem>
                        <asp:ListItem Text="Singapore" Value="Singapore"></asp:ListItem>
                        <asp:ListItem Text="Johore" Value="Johore"></asp:ListItem>
                        <asp:ListItem Text="Kuala Lumpur" Value ="Kuala Lumpur"></asp:ListItem>
                    </asp:DropDownList>
                </td>
            </tr>
            <tr>
                <td>
                    Meet-Up Location:
                </td>
                <td>
                    <asp:TextBox ID="uT_MeetLoc" runat="server" AutoPostBack="false" pattern="[A-Z0-9'-@#*()]+[A-Za-z0-9 '-@#*()]{1,}" title="Meeting Location must start with uppercase letters followed by lowercase letters. Only Alphanumeric and '-@#*() characters allowed. e.g. Your House"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td>
                    Max Tourists:
                </td>
                <td>
                    <asp:DropDownList ID="uT_PartiCount" runat="server" Width="165px" AutoPostBack="false">
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
                <td style="height: 60px">
                    Description:
                </td>
                <td style="height: 60px">
                    <asp:TextBox ID="uT_Desc" runat="server" Width="250px" Height="120px" TextMode="MultiLine" AutoPostBack="false" pattern="[A-Za-z0-9 '-@#*,.()]{1,}" title="Description name must start with uppercase letters followed by lowercase letters. Only Alphanumeric and '-@#*,.() characters allowed."></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td style="height: 10px" ></td>
                </tr>
                <tr>
                    <td style="width: 160px"></td>
                    <td style="width: 80px">
                        <asp:Button ID="TU_Update" runat="server" Text="Confirm" OnClick="TU_Update_Click" Width="70px"/>&nbsp;&nbsp;&nbsp;<asp:Button ID="TU_Cancel" runat="server" Text="Cancel"  OnClick="TU_Cancel_Click" Width="70px" UseSubmitBehavior="False" />
                    </td>
                </tr>
        </table>
        <br />
    </div>
</asp:Content>