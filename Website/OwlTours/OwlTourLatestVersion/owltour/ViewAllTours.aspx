<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="ViewAllTours.aspx.cs" Inherits="owltour.ViewAllTours" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="gridPad">
        <br />
        <div><p style="font-size:25px"><b>All Available Tours</b></p></div>
    <br />
    <div>Search Tour:
        <asp:TextBox ID="searchBox" runat="server" style="width: 380px"></asp:TextBox>
        <asp:DropDownList ID="searchBy" runat="server" Width="180px">
            <asp:ListItem Enabled="true" Text="Select Search Criteria"></asp:ListItem>
            <asp:ListItem Text="Tour Name"></asp:ListItem>
            <asp:ListItem Text="Tour Guide"></asp:ListItem>
            <asp:ListItem Text="Area"></asp:ListItem>
        </asp:DropDownList>
        <asp:CheckBox ID="full" runat="server" Text="All Tours" Font-Size="Small"></asp:CheckBox>
        <asp:Button ID="searchBtn" runat="server" Text="Search" OnClick="BtnSearch_Click" />
    </div>
    <br />
    <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataKeyNames="TourID" DataSourceID="SqlDataSource1" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView1_SelectedIndexChanged" Width="80%" AllowSorting="True" OnPageIndexChanging="grdView_PageIndexChanging" AllowPaging="true" PageSize="10" AutoPostBack="false">
        <AlternatingRowStyle BackColor="#e7eded" />
        <EmptyDataTemplate>No tours found.</EmptyDataTemplate>
        <Columns>
            <asp:BoundField DataField="TourID" HeaderText="#" InsertVisible="False" ReadOnly="True" SortExpression="TourID" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Right" /></asp:BoundField>
            <asp:BoundField DataField="TourName" HeaderText="Tour Name" SortExpression="TourName" ItemStyle-Width="80px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="TourDate" HeaderText="Date" SortExpression="TourDate" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller" DataFormatString="{0:d}"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="Area" HeaderText="Area" SortExpression="Area" ItemStyle-Width="80px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="T_MeetLoc" HeaderText="Meet-Up Loc" SortExpression="T_MeetLoc" ItemStyle-Width="80px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="Parti_count" HeaderText="Tourists Joined" SortExpression="Parti_count" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="T_Participants" HeaderText="Max Tourists." SortExpression="T_Participants" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="T_Desc" HeaderText="Description" SortExpression="T_Desc" ItemStyle-Width="200px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Left" /></asp:BoundField>
            <asp:BoundField DataField="userID" HeaderText="guideID" SortExpression="userID" ItemStyle-Width="80px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
            <asp:BoundField DataField="TourGuideName" HeaderText="Guide Name" SortExpression="TourGuideName" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller" ><ItemStyle HorizontalAlign="Left" /></asp:BoundField>
            <asp:CommandField ShowSelectButton="True" SelectText="Join" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" />
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
    <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString %>" ProviderName="<%$ ConnectionStrings:ConnectionString.ProviderName %>" SelectCommand="SELECT DISTINCT Tours.TourID, Tours.TourName, Tours.TourDate, Tours.Area, Tours.T_MeetLoc, Tours.Parti_count, Tours.T_Participants, Tours.T_Desc, Tours.userID, Tours.TourGuideName FROM Tours LEFT JOIN Bookings ON Tours.TourID = Bookings.b_TourID WHERE (Tours.TourDate &gt;= NOW() AND Tours.userID &lt;&gt; ? AND Tours.Parti_count  &lt; Tours.T_Participants AND Tours.TourID NOT IN (SELECT Bookings.b_TourID FROM Bookings WHERE Bookings.b_userID = ?)) ORDER BY Tours.TourDate">
        <SelectParameters>
            <asp:SessionParameter Name="?" SessionField="userID" />
            <asp:SessionParameter Name="?" SessionField="userID" />
        </SelectParameters>
    </asp:SqlDataSource>
        <br />
        <div>
            <asp:Button ID="Join_Button" runat="server" Text="Join Selected Tour Group" OnClick="Join_Button_Click" />
        </div>
    </div>
    <br />
</asp:Content>
