<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="ViewBookedTours.aspx.cs" Inherits="owltour.ViewBookedTours"  Debug="true"%>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="gridPad">
        <br />
        <div>Your Upcoming Booked Tours:</div>
    <br />
    <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataSourceID="SqlDataSource1" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView1_SelectedIndexChanged" Width="80%" AllowSorting="True" OnPageIndexChanging="grdView_PageIndexChanging" AllowPaging="True">
        <AlternatingRowStyle BackColor="#e7eded" />
        <EmptyDataTemplate>No upcoming tours found. Go join one!</EmptyDataTemplate>
        <Columns>
            <asp:BoundField DataField="b_TourID" HeaderText="#" SortExpression="b_TourID" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass="hideGridColumn" ItemStyle-CssClass="hideGridColumn"><HeaderStyle CssClass="hideGridColumn"></HeaderStyle><ItemStyle CssClass="hideGridColumn" Font-Size="Smaller"></ItemStyle></asp:BoundField>
            <asp:BoundField DataField="b_Name" HeaderText="Your Name" SortExpression="b_Name" ItemStyle-Width="120px" ItemStyle-Font-Size="Smaller" ItemStyle-HorizontalAlign="Center"><ItemStyle Font-Size="Smaller" ></ItemStyle></asp:BoundField>
            <asp:BoundField DataField="b_TourName" HeaderText="Tour Name" SortExpression="b_TourName" ItemStyle-Width="150px" ItemStyle-Font-Size="Smaller" ItemStyle-HorizontalAlign="Center"><ItemStyle Font-Size="Smaller" ></ItemStyle></asp:BoundField>
            <asp:BoundField DataField="b_TourDate" HeaderText="Date" SortExpression="b_TourDate" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller" DataFormatString="{0:d}" ItemStyle-HorizontalAlign="Center"><ItemStyle Font-Size="Smaller"></ItemStyle></asp:BoundField>
            <asp:BoundField DataField="b_Area" HeaderText="Area" SortExpression="b_Area" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller"><ItemStyle Font-Size="Smaller" HorizontalAlign="Center"></ItemStyle></asp:BoundField>
            <asp:BoundField DataField="b_MeetLoc" HeaderText="Meet-Up Location" SortExpression="b_MeetLoc" ItemStyle-Width="150px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="b_Desc" HeaderText="Description" SortExpression="b_Desc" ItemStyle-Width="400px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Left" /></asp:BoundField>
            <asp:BoundField DataField="b_GuideName" HeaderText="Tour Guide Name" SortExpression="b_GuideName" ItemStyle-Width="120px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="b_TourGuideID" HeaderText="Guide ID" SortExpression="b_TourGuideID" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass="hideGridColumn" ItemStyle-CssClass="hideGridColumn" ><HeaderStyle CssClass="hideGridColumn"></HeaderStyle><ItemStyle CssClass="hideGridColumn" Font-Size="Smaller"></ItemStyle></asp:BoundField>
            <asp:CommandField SelectText="Withdraw" ShowSelectButton="True" ItemStyle-Font-Size="Smaller"/>
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
    <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString %>" ProviderName="<%$ ConnectionStrings:ConnectionString.ProviderName %>" SelectCommand="SELECT [b_TourID], [b_Name], [b_TourName], [b_TourDate], [b_Area], [b_MeetLoc], [b_Desc], [b_GuideName], [b_TourGuideID] FROM [Bookings] WHERE [b_userID] = ? AND b_TourDate  &gt;= NOW() ORDER BY [b_TourDate]">
        <SelectParameters>
            <asp:SessionParameter Name="?" SessionField="userID" />
        </SelectParameters>
    </asp:SqlDataSource>
    <div>
        <br />
        <asp:Button ID="cancelTour" runat="server" Text="Withdraw from Tour" OnClick="cancelTour_Click" />
        <br />
        <br />
    </div>
    <div>Rate Recent Tour Guide:</div>
    <br/>
    <asp:GridView ID="GridView2" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataSourceID="SqlDataSource2" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView2_SelectedIndexChanged" Width="80%" AllowSorting="True">
        <AlternatingRowStyle BackColor="#e7eded" />
            <EmptyDataTemplate>No recent unrated tours.</EmptyDataTemplate>
            <Columns>
                <asp:BoundField DataField="b_TourID" HeaderText="#" SortExpression="b_TourID" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="b_TourName" HeaderText="Tour Name" SortExpression="b_TourName" ItemStyle-Width="120px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="b_TourDate" HeaderText="Date" SortExpression="b_TourDate" ItemStyle-Width="100px" DataFormatString="{0:d}" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="b_TourGuideID" HeaderText="GuideID" SortExpression="b_TourGuideID" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn" ItemStyle-HorizontalAlign="Center" />
                <asp:BoundField DataField="b_GuideName" HeaderText="Guide" SortExpression="b_GuideName" ItemStyle-Width="120px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:CommandField SelectText="Rate" ItemStyle-Font-Size="Smaller" ItemStyle-Width="50px" ItemStyle-HorizontalAlign="Center" ShowSelectButton="True" />
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
        <asp:SqlDataSource ID="SqlDataSource2" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString2 %>" ProviderName="<%$ ConnectionStrings:ConnectionString2.ProviderName %>" SelectCommand="SELECT [b_TourID], [b_TourName], [b_TourDate],  [b_TourGuideID], [b_GuideName]  FROM [Bookings] WHERE [b_userID] = ? AND b_TourDate  &lt;= NOW() ORDER BY [b_TourDate]">
            <SelectParameters>
                <asp:SessionParameter Name="?" SessionField="userID" />
            </SelectParameters>
        </asp:SqlDataSource>
        <br/>
    </div>
    
    <div id ="RateDiv" runat="server">
        <div class="enterinfotable">
            <table class="centertable">
            <col height='5'>
            <col width ='300'>
                <tr>
                    <td>
                        Rating:
                    </td>
                    <td>
                        <asp:DropDownList ID="rating" runat="server" Width="120px">
                            <asp:ListItem Enabled="true" Text="Select Rating"></asp:ListItem>
                            <asp:ListItem Text="★" Value='1'></asp:ListItem>
                            <asp:ListItem Text="★★" Value='2'></asp:ListItem>
                            <asp:ListItem Text="★★★" Value='3'></asp:ListItem>
                            <asp:ListItem Text="★★★★" Value='4'></asp:ListItem>
                            <asp:ListItem Text="★★★★★" Value='5'></asp:ListItem>
                        </asp:DropDownList>
                    </td>
                </tr>
                <tr>
                    <td style="height: 10px" ></td>
                </tr>
                <tr>
                    <td style="width: 160px"></td>
                    <td style="width: 80px">
                        <asp:Button ID="Rate_Button" runat="server" Text="Submit" OnClick="Rate_Button_Click" Width="70px"/>
                    </td>
                </tr>
            </table>
        </div>
    </div>
    <br />
</asp:Content>