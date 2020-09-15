<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="Inbox.aspx.cs" Inherits="owltour.Inbox" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
    <table class="gridPad">
        <br />
        <tr>
            <td id="sendMsgd" runat="server"><asp:Button ID="sendMsg" runat="server" Text="New" OnClick="send_Click" ToolTip="Send a New Message" Width="70px" /></td>
            <td id="msgSpace" runat="server"></td>
            <td><asp:Button ID="recMsg" runat="server" Text="Inbox" OnClick="rec_Click" ToolTop="View Received Messages" Width="70px"/></td>
        </tr>
    </table>
    <br />
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <%--inbox--%>
    <div class="gridPad">
        <asp:GridView ID="inboxView" runat="server" AutoGenerateColumns="False" DataSourceID="inboxConn" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView1_SelectedIndexChanged" Width="80%" OnPageIndexChanging="grdView1_PageIndexChanging" AllowPaging="true" PageSize="10">
            <AlternatingRowStyle BackColor="#e7eded" />
            <EmptyDataTemplate>Inbox empty.</EmptyDataTemplate>
            <Columns>
                <asp:BoundField DataField="sendersID" HeaderText="ID" SortExpression="sendersID" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn" />
                <asp:BoundField DataField="Username" HeaderText="From" SortExpression="Username" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" />
                <asp:BoundField DataField="message" HeaderText="Message" SortExpression="message" ItemStyle-Width="700px" ItemStyle-Font-Size="Smaller"/>
                <asp:BoundField DataField="isRead" HeaderText="isRead" SortExpression="isRead" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn" />
                <asp:BoundField DataField="msgID" HeaderText="msgID" SortExpression="msgID" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn" />
                <asp:CommandField SelectText="View Message" ShowSelectButton="True" ItemStyle-HorizontalAlign="Center" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller"/>
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
        <asp:SqlDataSource ID="inboxConn" runat="server" ConnectionString="<%$ ConnectionStrings:ConnectionString %>" ProviderName="<%$ ConnectionStrings:ConnectionString.ProviderName %>" SelectCommand="SELECT Inbox.sendersID, Users.Username, Inbox.message, Inbox.isRead, Inbox.msgID FROM Inbox INNER JOIN Users ON Inbox.sendersID = Users.userID WHERE ((Inbox.isDeleted = ?) AND (Inbox.recepientsID = ?))">
            <SelectParameters>
                <asp:Parameter DefaultValue="No" Name="isDeleted" Type="String" />
                <asp:SessionParameter Name="recepientsID" SessionField="userID" Type="Int32" />
            </SelectParameters>
        </asp:SqlDataSource>
    </div>
    <%--choose user to send msg to--%>
    <div class="gridPad">
        <div id="searchUser" runat="server">Search User:
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
        <asp:GridView ID="searchProfile" runat="server" AutoGenerateColumns="False" BackColor="#c7d6d6" BorderColor="#334144" BorderWidth="1px" CellPadding="5" DataSourceID="SqlDataSource1" ForeColor="Black" GridLines="None" OnSelectedIndexChanged="GridView2_SelectedIndexChanged" Width="80%" AllowSorting="True" OnPageIndexChanging="grdView2_PageIndexChanging" AllowPaging="true" PageSize="10">
            <AlternatingRowStyle BackColor="#e7eded" />
            <EmptyDataTemplate>No such user.</EmptyDataTemplate>
            <Columns>
                <asp:BoundField DataField="userID" HeaderText="userID" SortExpression="userID" ItemStyle-Width="30px" ItemStyle-Font-Size="Smaller" HeaderStyle-CssClass = "hideGridColumn" ItemStyle-CssClass="hideGridColumn"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="Username" HeaderText="Username" SortExpression="Username" ItemStyle-Width="150px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="firstName" HeaderText="First Name" SortExpression="firstName" ItemStyle-Width="150px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="lastName" HeaderText="Last Name" SortExpression="lastName" ItemStyle-Width="150px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:BoundField DataField="Email" HeaderText="Email" SortExpression="Email" ItemStyle-Width="200px" ItemStyle-Font-Size="Smaller"><ItemStyle HorizontalAlign="Center" /></asp:BoundField>
                <asp:CommandField SelectText="Send Message" ShowSelectButton="True" ItemStyle-HorizontalAlign="Center" ItemStyle-Width="50px" ItemStyle-Font-Size="Smaller"/>
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
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:Search Profile %>" ProviderName="<%$ ConnectionStrings:Search Profile.ProviderName %>" SelectCommand="SELECT [userID], [Username], [firstName], [lastName], [Email] FROM [Users]">
        </asp:SqlDataSource>
        <br />
    </div>
    <%--view msg--%>
    <div class="enterinfotable" id ="inMsgDiv" runat="server">
        <table class="centertable">
            <col height='5'>
            <col width ='300'>
            <tr>
                <td style="width: 75px">
                    From:
                </td>
                <td>
                    <asp:Label ID="senderName" runat="server" Width="150px" Text=""/>
                </td>
            </tr>
            <tr>
                <td style="width: 75px">
                    Message:
                </td>
                <td>
                    <asp:TextBox ID="inMsg" runat="server" Width="500px" Height="150px" TextMode="MultiLine" ReadOnly="true" Scrollbar="enabled"/>
                </td>
            </tr>
            <tr><td style="width: 75px"></td></tr>
            <tr>
                <td style="width: 75px"></td>
                <td>
                    <asp:Button ID="inboxReply" runat="server" Text="Reply" OnClick="reply_Click" />
                    <asp:Label ID="inboxReplySpace" runat="server" Width="10px"></asp:Label>
                    <asp:Button ID="inboxDelete" runat="server" Text="Delete" OnClick="delete_Click" />
                </td>
            </tr>
        </table>
    </div>
    <br />

    <%--send msg--%>
    <div class="enterinfotable" id ="outMsgDiv" runat="server">
        <table class="centertable">
            <col height='5'>
            <col width ='300'>
            <tr id="rowReply" runat="server">
                <td style="width: 75px">
                    To:
                </td>
                <td>
                    <asp:Label ID="recepientName" runat="server" Width="150px" Text=""/>
                </td>
            </tr>
            <tr>
                <td style="width: 75px">
                    Message:
                </td>
                <td>
                    <asp:TextBox ID="outMsg" runat="server" Width="500px" Height="150px" TextMode="MultiLine" ReadOnly="false" Scrollbar="enabled"/>
                </td>
            </tr>
            <tr><td style="width: 75px"></td></tr>
            <tr>
                <td style="width: 75px"></td>
                <td>
                    <asp:Button ID="sendReplyClick" runat="server" Text="Send" OnClick="sendMsg_reply_Click" />
                    <asp:Button ID="sendNewClick" runat="server" Text="Send" OnClick="sendMsg_new_Click" />
                </td>
            </tr>
        </table>
    </div> 
    <br />
</asp:Content>