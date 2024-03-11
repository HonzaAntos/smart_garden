<!DOCTYPE html>
<html lang="cs">
<head>

     <title>Úvodní Stránka</title>

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
                         <li class="active"><a href="home.php">Domů</a></li>
                         <li><a href="our-products.php">Naše Produkty</a></li>
                         <li><a href="index.php">Naměřená Data</a></li>
                         <li><a href="contact-us.php">Kontaktujte Nás</a></li>

                    </ul>
               </div>

          </div>
     </section>

     <!-- HOME -->
     <section id="home">
          <div class="row">
               <div class="owl-carousel owl-theme home-slider">
                    <div class="item item-first">
                         <div class="caption">
                              <div class="container">
                                   <div class="col-md-6 col-sm-12">
                                        <h1>Bakalářská práce</h1>
                                        <h3>Řídící systém pro chytrou zahradu</h3>
                                        <a href="our-products.php" class="section-btn btn btn-default">Zjistit Více</a>
                                   </div>
                              </div>
                         </div>
                    </div>

                    <div class="item item-second">
                         <div class="caption">
                              <div class="container">
                                   <div class="col-md-6 col-sm-12">
                                        <h1>Hladinoměr</h1>
                                        <h3>Plováčkový hladinoměr vhodný pro měření výšky hladiny ve studni.</h3>
                                        <a href="water-level-detector.php" class="section-btn btn btn-default">Zjistit Více</a>
                                   </div>
                              </div>
                         </div>
                    </div>

                    <div class="item item-third">
                         <div class="caption">
                              <div class="container">
                                   <div class="col-md-6 col-sm-12">
                                        <h1>Koncentrátor</h1>
                                        <h3>Pohodlný přehled o veškerých datech ze zahrady na jednom místě z pohodlí domova.</h3>
                                        <a href="home-station.php" class="section-btn btn btn-default">Zjistit Více</a>
                                   </div>
                              </div>
                         </div>
                    </div>
               </div>
          </div>
     </section>

     <main>
          <section>
               <div class="container">
                    <div class="row">
                         <div class="col-md-12 col-sm-12">
                              <div class="text-center">
                                   <h2>Něco o projektu</h2>

                                   <br>

                                   <p class="lead">Tato bakalářská práce má za úkol navrhnout koncepci distribuovaného řídícího systému pro chytrou zahradu. Definovat požadavky pro každou vrstvu řídícího systému a vybrat vhodnou desku s mikrokontroléry, které budou schopny komunikovat s vývojovým prostředím Arduino IDE. Pro demonstraci je navrhnut model hladinoměru, který snímá výšku hladiny vody ve studni. Tento modul odesílá změřená data o vrstvu výše a zároveň je zobrazuje lokálně na displeji modulu. Tímto řešením máme modul, který dokáže být samostatný v řídícím systému. </p>
                              </div>
                         </div>
                    </div>
               </div>
          </section>
          <section>
               <div class="container">
                    <div class="row">
                         <div class="col-md-12 col-sm-12">
                              <div class="section-title text-center">
                                   <h2>Novinky <small>Pro systém chytré zahrady</small></h2>
                              </div>
                         </div>

                         <div class="col-md-4 col-sm-4">
                              <div class="courses-thumb courses-thumb-secondary">
                                   <div class="courses-top">
                                        <div class="courses-image">
                                             <img src="images/product-1-720x480.jpg" class="img-responsive" alt="">
                                        </div>
                                   </div>

                                   <div class="courses-detail">
                                        <h3><a href="our-products.php">Samostatný model plováčkového hladinoměru</a></h3>
                                   </div>

                                   <div class="courses-info">
                                        <a href="water-level-detector.php" class="section-btn btn btn-primary btn-block">Zjistit Více</a>
                                   </div>
                              </div>
                         </div>

                         <div class="col-md-4 col-sm-4">
                              <div class="courses-thumb courses-thumb-secondary">
                                   <div class="courses-top">
                                        <div class="courses-image">
                                             <img src="images/product-02-720x480.jpg" class="img-responsive" alt="">
                                        </div>
                                   </div>

                                   <div class="courses-detail">
                                        <h3><a href="our-products.php">Modul domácího HUBu pro sběr veškerých dat</a></h3>
                                   </div>

                                   <div class="courses-info">
                                        <a href="home-station.php" class="section-btn btn btn-primary btn-block">Zjistit Více</a>
                                   </div>
                              </div>
                         </div>

                         <div class="col-md-4 col-sm-4">
                              <div class="courses-thumb courses-thumb-secondary">
                                   <div class="courses-top">
                                        <div class="courses-image">
                                             <img src="images/product-3-720x4800.jpg" class="img-responsive" alt="">
                                        </div>
                                   </div>

                                   <div class="courses-detail">
                                        <h3><a href="our-products.php">Databázový server se všemi nashromážděnými daty</a></h3>
                                   </div>

                                   <div class="courses-info">
                                        <a href="database.php" class="section-btn btn btn-primary btn-block">Zjistit Více</a>
                                   </div>
                              </div>
                         </div>
                    </div>
               </div>
          </section>
     </main>

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