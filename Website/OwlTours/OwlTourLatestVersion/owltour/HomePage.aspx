<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="HomePage.aspx.cs" Inherits="owltour.HomePage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
    <div class="msgdiv">
        <br />
        <asp:Label class="font-weight-light" ID="welcomeMsg" runat="server"></asp:Label>
    </div>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <br />      
    <div class="container h-100">
        <div class="row h-100 align-items-center">
            <div class="col-12 text-center">
                <h1 class="font-weight-light">We take you to places you don't want to go</h1>
                <p class="lead">A great way to start your holiday!</p>
            </div>
        </div>
    </div>
    <br />
    <div class="msgdiv">
        <asp:Label class="lead" ID="susMsg" runat="server" Font-Size="X-Large"></asp:Label>
    </div>
    <br />
</asp:Content>
