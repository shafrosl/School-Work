<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="SearchProfile.aspx.cs" Inherits="owltour.SearchProfile" Debug="true"%>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <div class="gridPad">
        <br />
        <div><p style="font-size:25px"><b>All Users of Owl Tours</b></p></div>
        <div>Search User:
            <asp:TextBox ID="searchBox" runat="server" Width="450px"></asp:TextBox>
            <asp:DropDownList ID="searchBy" runat="server" Width="180px">
                <asp:ListItem Enabled="true" Text="Select Search Criteria"></asp:ListItem>
                <asp:ListItem Text="Username"></asp:ListItem>
                <asp:ListItem Text="First Name"></asp:ListItem>
                <asp:ListItem Text="Last Name"></asp:ListItem>
                <asp:ListItem Text="E-Mail"></asp:ListItem>
            </asp:DropDownList>
            <asp:Button ID="searchBtn" runat="server" Text="Search" OnClick="BtnSearch_Click" />
        </div>
        <br />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataSourceID="SqlDataSource1" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView1_SelectedIndexChanged" Width="80%" AllowSorting="True" DataKeyNames="userID" OnPageIndexChanging="grdView_PageIndexChanging" AllowPaging="true" PageSize="10" AutoPostBack="false">
            <AlternatingRowStyle BackColor="#e7eded" />
            <EmptyDataTemplate>No such user.</EmptyDataTemplate>
            <Columns>
                <asp:BoundField DataField="userID" HeaderText="#" SortExpression="userID" ItemStyle-Width="15px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass="hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="Username" HeaderText="Username" SortExpression="Username" ItemStyle-Width="120px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="firstName" HeaderText="First Name" SortExpression="firstName" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="lastName" HeaderText="Last Name" SortExpression="lastName" ItemStyle-Width="100px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="Email" HeaderText="Email" SortExpression="Email" ItemStyle-Width="200px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="avgRating" HeaderText="Avg. Rating" SortExpression="avgRating" ItemStyle-Width="25px" ItemStyle-Font-Size="Smaller" DataFormatString="{0:0.00}"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="isSuspended" HeaderText="Suspended?" SortExpression="isSuspended" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:CommandField SelectText="Change Suspension Status" ShowSelectButton="True" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller"/>
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
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:Search Profile %>" ProviderName="<%$ ConnectionStrings:Search Profile.ProviderName %>" SelectCommand="SELECT [userID], [Username], [firstName], [lastName], [Email], [isSuspended], [avgRating] FROM [Users]">
        </asp:SqlDataSource>
        <br />
        <div>
            <asp:Button ID="susAcct" runat="server" Text="Suspend Account" OnClick="susAcct_Click" />
            <asp:Button ID="unSusAcct" runat="server" Text="Un-Suspend Account" OnClick="unSusAcct_Click" />
        </div>
    </div>
    <br />
</asp:Content>
