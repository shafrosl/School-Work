<%@ Page Language="C#" MasterPageFile="~/MasterPage.Master" AutoEventWireup="true" CodeBehind="AboutPage.aspx.cs" Inherits="owltour.AboutPage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="msg" runat="server">
    <div>
        <asp:Label ID="welcomeMsg" runat="server"></asp:Label>
    </div>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

    <section class="my-5">
        <div class="container">
            <div class="row">
                <div class="col-md-8 mx-auto">
                    <p>6 Students, one team taking charge of a tour page.</p>
                    <p>You happened to stumble upon our little site.</p>
                    <p>Perhaps you'd like to take a gamble, pick and choose your tour or tour-guide.</p>
                    <p>
                        We're just like airbnb but <b>TOURS!</b>
                    </p>
                    <p class="mb-0">
                        Created by <a href="Homepage.aspx" />TEAM OWLTOURS
                    </p>
                </div>
            </div>
        </div>
    </section>

</asp:Content>
