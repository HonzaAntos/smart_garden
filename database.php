<!DOCTYPE html>
<html lang="cs">
<head>

     <title>Databáze</title>

     <meta charset="UTF-8">
     <meta http-equiv="X-UA-Compatible" content="IE=Edge">
     <meta name="description" content="">
     <meta name="keywords" content="">
     <meta name="author" content="">
     <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">

     <link rel="stylesheet" href="css/bootstrap.min.css">
     <link rel="stylesheet" href="css/font-awesome.min.css">
     <link rel="stylesheet" href="css/owl.carousel.css">
     <link rel="stylesheet" href="css/owl.theme.default.min.css">

     <!-- MAIN CSS -->
     <link rel="stylesheet" href="css/style.css">

</head>
<body id="top" data-spy="scroll" data-target=".navbar-collapse" data-offset="50">

     <!-- PRE LOADER -->
     <section class="preloader">
          <div class="spinner">

               <span class="spinner-rotate"></span>

          </div>
     </section>


     <!-- MENU -->
     <section class="navbar custom-navbar navbar-fixed-top" role="navigation">
          <div class="container">

               <div class="navbar-header">
                    <button class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                         <span class="icon icon-bar"></span>
                         <span class="icon icon-bar"></span>
                         <span class="icon icon-bar"></span>
                    </button>

                    <!-- lOGO TEXT HERE -->
                    <a href="home.php" class="navbar-brand"><img src="images/TechCrowd_logo_crop.jpg" class="img-responsive" alt=""></a>
               </div>

               <!-- MENU LINKS -->
               <div class="collapse navbar-collapse">
                    <ul class="nav navbar-nav navbar-nav-first">
                         <li><a href="home.php">Domů</a></li>
                         <li><a href="our-products.php">Naše Produkty</a></li>
                         <li><a href="index.php">Naměřená Data</a></li>
                         <li><a href="contact-us.php">Kontaktujte Nás</a></li>
                    </ul>
               </div>

          </div>
     </section>

     <section>
          <div class="container">
               <h2>Databázový server se všemi nashromážděnými daty</h2>

               <p class="lead">
                    <i class="fa fa-user"></i> Jan Antoš &nbsp;&nbsp;&nbsp;
                    <i class="fa fa-calendar"></i> 09/02/2022 &nbsp;&nbsp;&nbsp;
               </p>

               <img src="images/other-image-fullscreen-3-1920x700.jpg" class="img-responsive" alt="">

               <br>

               <h3>Pohodlný přehled o veškerých datech ze zahrady na jednom místě z pohodlí domova.</h3>


               <p>Jako databázový server byl vybrán MariaDB, což je nástupce MySQL. MariaDB je multiplatformní databáze, která je volně šiřitelná a v dnešní době je hodně oblíbená. Vznikla z důvodu udržení licence svobodného softwaru MySQL. Zvolena byla hlavně z toho důvodu, že s ní máme zkušenost, dále kvůli implementovatelnosti v multiplatformním softwarovém balíčku XAMPP a také kvůli její jednoduché implementaci pomocí webového rozhraní phpMyAdmin, ke kterému se dostaneme později. </p>

               <p>Webový sever použitý v této práci je server Apache HTTP Server. Mezi jeho přednosti patří to, že software je volně šiřitelný a v současné době dodává prohlížečům na celém světě většinu internetových stránek. Další předností je, že je také implementován v multiplatformním balíčku XAMPP. </p>

               <br>

               <h4>XAMPP</h4>

               <img src="images/other-image-fullscreen-3-1-1920x7000.jpg" class="img-responsive" alt="">

               <br>

               <p> XAMPP je multiplatformní softwarový balíček vyvinutý firmou Apache Friends. Termín XAMPP dostalo podle neoficiální zdrojů podle prvních písmen použitých funkcí. X – multiplatformní (v angličtině cross-platform, kde cross je v překladu kříž), A – Apache, M – MariaDB (dříve MySQL), P – PHP, P – Perl. XAMPP slouží pro vytvoření lokálního serveru pro vývojáře na testování a vývoj. Na obrázku 17 je zobrazen kontrolní panel pro XAMPP, kde se jednoduše spustí Apache nebo MySQL server pouhým stisknutím tlačítka Start.  </p>

               <br>

               <h4>Předpokládaná pořizovací cena: </h4>

               <p> 999 Kč s DPH za první zařízení (další +499 Kč)</p>

               <br>
               <br>
          </div>
     </section>

      <!-- FOOTER -->
         <footer id="footer">
              <div class="container">
                   <div class="row">

                        <div class="col-md-4 col-sm-6">
                             <div class="footer-info">
                                  <div class="section-title">
                                       <h2>Sídlo</h2>
                                  </div>
                                  <address>
                                       <p>Kounicova 46/48, 602 00 Brno-Královo Pole</p>
                                  </address>

                                  <ul class="social-icon">
                                       <li><a href="https://www.facebook.com/honza.antos.90" class="fa fa-facebook-square" attr="facebook icon"></a></li>
                                       <li><a href="#" class="fa fa-twitter"></a></li>
                                       <li><a href="https://www.instagram.com/_enty_/" class="fa fa-instagram"></a></li>
                                  </ul>

                                  <div class="copyright-text">
                                       <p>Copyright &copy; 2022 TechCrowd & Jan Antoš</p>
                                  </div>
                             </div>
                        </div>

                        <div class="col-md-4 col-sm-6">
                             <div class="footer-info">
                                  <div class="section-title">
                                       <h2>Kontakty</h2>
                                  </div>
                                  <address>
                                       <p>+420 735 549 704 </p>
                                       <p><a href="mailto:honza.ant@email.cz">honza.ant@email.cz</a></p>
                                  </address>

                                  <div class="footer_menu">
                                       <h2>Rychlé Odkazy</h2>
                                       <ul>
                                        <li><a href="home.php">Domů</a></li>
                                        <li><a href="https://www.techcrowd.cz/">Stránka TechCrowd</a></li>
                                        <li><a href="index.php">Naměřená data</a></li>
                                        <li><a href="contact-us.php">Kontaktujte nás</a></li>
                                       </ul>
                                  </div>
                             </div>
                        </div>
                   </div>
              </div>
         </footer>

         <!-- SCRIPTS -->
         <script src="js/jquery.js"></script>
         <script src="js/bootstrap.min.js"></script>
         <script src="js/owl.carousel.min.js"></script>
         <script src="js/smoothscroll.js"></script>
         <script src="js/custom.js"></script>

    </body>
    </html>