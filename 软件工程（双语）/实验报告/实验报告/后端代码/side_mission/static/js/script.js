
/* Java Script File */

jQuery.noConflict()(function ($) {

    'use strict';
	
    var isMobile = {
        Android: function() {
            return navigator.userAgent.match(/Android/i);
        },
        BlackBerry: function() {
            return navigator.userAgent.match(/BlackBerry/i);
        },
        iPhone: function() {
            return navigator.userAgent.match(/iPhone/i);
        },
        iPad: function() {
            return navigator.userAgent.match(/iPad/i);
        },
        iPod: function() {
            return navigator.userAgent.match(/iPod/i);
        },
        iOS: function() {
            return navigator.userAgent.match(/iPhone|iPad|iPod/i);
        },
        Opera: function() {
            return navigator.userAgent.match(/Opera Mini/i);
        },
        Windows: function() {
            return navigator.userAgent.match(/IEMobile/i);
        },
        any: function() {
            return (isMobile.Android() || isMobile.BlackBerry() || isMobile.iOS() || isMobile.Opera() || isMobile.Windows());
        }
    };


    // ******************************//
    // Progress Bar
    // ******************************//

    function progress_bar(){

        $('.progress-bar').each(function(){ 

            $(this).appear(function(){          
                var percent = parseInt($(this).find('span').text(),10);
                var $endNum = percent;
                        $(this).find('.progress-inner').velocity({
                    width: percent + '%'
                },{ 
                    duration: 1200 
                }, 'ease-in-out');

                if (typeof $.fn.countTo !== 'undefined') {

                    $(this).find('span').countTo({
                        from: 0,
                        to: $endNum,
                        speed: 1200,
                        refreshInterval: 30
                    }); 

                }
                
            });
        }); 

    }


    // ******************************//
    // Counter Up
    // ******************************//

    function counterItem(){
        $('.counter-item').each(function(){ 
            $(this).appear(function(){          
                var percent = parseInt($(this).find('i').text(),10);
                var $endNum = percent;

                $(this).find('i').countTo({
                    from: 0,
                    to: $endNum,
                    speed: 1200,
                    refreshInterval: 30
                });  
                
            });
        }); 

    }


    // ******************************//
    // Scroll to Top
    // ******************************//

    function scrollTop(){
        var offset = 300,
        scroll_top_duration = 350,
        $back_to_top = $('.scroll-top');
        $(window).on('scroll', function(){
            if($(this).scrollTop() > offset ) {
                $back_to_top.addClass('scroll-top-visible').removeClass('scroll-top-hidden');
            } 
			else {
                $back_to_top.addClass('scroll-top-hidden').removeClass('scroll-top-visible');
            }
        });
        $back_to_top.on('click', function() {
            $('html, body').animate({
                scrollTop: 0
            }, scroll_top_duration);
            return false;
        });

    }


    // ******************************//
    // Overlay Menu
    // ******************************//

    function sweetMenu(){
        var $menu = $('#fullscreen-navigation'),
            $header = $('header'),
            $body = $('body'),
            $fn = $('#fullscreen-navigation'),
            $fnToggle = $('.fullscreen-menu-toggle'),
            $window = $(window);
            if($body.hasClass('header-fixed')){
                $body.stickyPanel({
                    slickyClass: "fixedheader",
                    extraOffset: 0,
                    fakeBlock: false,
                    scrollClasses: true
                });   
            }

        $menu.find('.menu-item-has-children > a').on('click', function(e) {
            e.preventDefault();
            if ($(this).next('ul').is(':visible')) {
                $(this).removeClass('sub-active').next('ul').slideUp(250);
            } else {
                $('.menu-item-has-children > a').removeClass('sub-active').next('ul').slideUp(250);
                $(this).addClass('sub-active').next('ul').slideToggle(250);
            }
        });

        var fnOpen = false;
        var fnToggleFunc = function() {
            fnOpen = !fnOpen;
            $body.toggleClass('fullscreen-nav-open');
            $fn.stop().fadeToggle(500);
            $('.fullscreen-menu-toggle > .menu-bars').toggleClass('active');
            return false;
        };
        $fnToggle.on('click', fnToggleFunc);
        $(document).on('keyup', function(e) {
            if (e.keyCode == 27 && fnOpen) {
                fnToggleFunc();
            }
        });
		
        $fn.find('li:not(.menu-item-has-children) > a').one('click', function() {
            fnToggleFunc();
            return true;
        });

        $menu.on('click', function(){
            fnToggleFunc();
            return true;
        });

        $('.inner-wrap, .fullscreen-menu-toggle').on('click', function(e){
            e.stopPropagation();
        });

    }

$(document).ready(function() {


    // ******************************//
    // Functions Call
    // ******************************//
	
    progress_bar();
    counterItem();
    scrollTop();
    sweetMenu();


    // ******************************//
    // Tooltip
    // ******************************//

    $('[data-toggle=tooltip]').tooltipster({
        theme: 'mini-tooltip',
        touchDevices: false,
        trigger: 'hover'
    });

    // ******************************//
    // Parallax
    // ******************************//
	
    $('.jarallax').jarallax({
        speed: 0.2,
        noAndroid: true
    });


    // ******************************//
    // Blog Masonry
    // ******************************//

    $('.blog-post.masonry').imagesLoaded(function(){
        $('.blog-post.masonry').isotope({
            layoutMode: 'masonry',
            transitionDuration: '0.3s'
        });
    });


    // ******************************//
    // Animsition
    // ******************************//
    
    if($('.animsition').length) {
        $('.animsition').animsition({
            inClass: 'fade-in',
            outClass: 'fade-out',
            inDuration: 1200,
            outDuration: 1200,
            linkElement: '.animsition-link',
            loading: true,
            loadingParentElement: 'body',
            loadingClass: 'animsition-loading',
            loadingInner: '<div class="preloader"></div>',
            timeout: false,
            timeoutCountdown: 5000,
            onLoadEvent: true,
            browser: [
                'animation-duration', 
                '-webkit-animation-duration', 
                '-o-animation-duration'],
            overlay: false,
            overlayClass: 'animsition-overlay-slide',
            overlayParentElement: 'body',
            transition: function(url) {
                window.location.href = url;
            }
        });

        $('.animsition').on('animsition.outStart', function(){
            $('body').removeClass('fullscreen-nav-open');
        });

    }

    // ******************************//
    // Fancybox
    // ******************************//

    $('.fancybox').fancybox({
        openEffect  : 'none',
        closeEffect : 'none',
        closeBtn: false,
        padding: 0,
        beforeShow : function() {
            var alt = this.element.find('img').attr('alt');
            this.inner.find('img').attr('alt', alt);
            this.title = alt;
        }
    });


    // ******************************//
    // Image SLider
    // ******************************//
	
    var $animDur = 1000,
        $animDelay = ($animDur/4)-20,
        $animSpeed = $animDur-$animDelay;
    var $navW = '<div class="image-slider-nav">\
                <a href="#" class="flex-prev"></a>\
                <a href="#" class="flex-next"></a>\
                </div>';

    var $imageSW = $('.image-slider-wrap');
    $imageSW.each(function(){
        var $this = $(this);
        var $imageContainer = $this.find('.image-slider'),
            slides = $imageContainer.find('.flexslider li');
        if ($(this).attr('data-visible-nav') == 'true') {
                $this.find('.flexslider').prepend($navW);
        }
        $this.find('.image-slider-nav a.flex-prev').on('click', function(e){
            e.preventDefault();
            $imageContainer.flexslider('prev');
        });
        $this.find('.image-slider-nav a.flex-next').on('click', function(e){
            e.preventDefault();
            $imageContainer.flexslider('next');
        });
        $imageContainer.flexslider({
            selector: '.flexslider > ul > li',
            animation: 'fade',
            controlNav: $(this).data('visible-dots') || false,
            directionNav: false,
            animationLoop: false,
            slideshow: false,
            slideshowSpeed: 4000,
            animationSpeed: $animSpeed,
            itemMargin: 0,
            initDelay: 0,
            move: 4,
            minItems: 4,
            maxItems: 4,
            before: function(slider){ 
                var $currentSlide = slider.slides.eq(slider.currentSlide),
                    $nextSlide = slider.slides.eq(slider.currentSlide+1),
                    $prevSlide = slider.slides.eq(slider.currentSlide-1);

                $nextSlide.find('img').css({
                    'opacity': 0
                });

                $prevSlide.find('img').css({
                    'opacity': 0
                });

                $this.find('.blind-01, .blind-02').velocity({
                    translateX: '-100%'
                }, 0);

                $this.find('.blind-01').velocity({
                    translateX: '100%'
                }, { 
                    duration: $animDur
                });

                $this.find('.blind-02').velocity({
                    translateX: '100%'
                }, { 
                    duration: $animDur,
                    delay: $animDelay
                }); 
            },
            after: function(slider){
                var $currentSlide = slider.slides.eq(slider.currentSlide);
                $currentSlide.find('img').velocity({
                    'opacity': 1
                }, {
                    duration: $animDur
                });
            }
        });
    });


    // ******************************//
    // Google Map
    // ******************************//

    function initialize_map() {
        $('#map').each(function() {
            var $t = $(this),
                mapZoom = 15,
                mapLat = $t.attr('data-lat'),
                mapLng = $t.attr('data-lng');
            if ($t.attr('data-zoom') !== undefined) {
                mapZoom = parseInt($t.attr('data-zoom'), 10);
            }
            // Create an array of styles.
            var styles = [{"featureType":"water","elementType":"geometry","stylers":[{"color":"#e9e9e9"},{"lightness":17}]},{"featureType":"landscape","elementType":"geometry","stylers":[{"color":"#f5f5f5"},{"lightness":20}]},{"featureType":"road.highway","elementType":"geometry.fill","stylers":[{"color":"#ffffff"},{"lightness":17}]},{"featureType":"road.highway","elementType":"geometry.stroke","stylers":[{"color":"#ffffff"},{"lightness":29},{"weight":0.2}]},{"featureType":"road.arterial","elementType":"geometry","stylers":[{"color":"#ffffff"},{"lightness":18}]},{"featureType":"road.local","elementType":"geometry","stylers":[{"color":"#ffffff"},{"lightness":16}]},{"featureType":"poi","elementType":"geometry","stylers":[{"color":"#f5f5f5"},{"lightness":21}]},{"featureType":"poi.park","elementType":"geometry","stylers":[{"color":"#dedede"},{"lightness":21}]},{"elementType":"labels.text.stroke","stylers":[{"visibility":"on"},{"color":"#ffffff"},{"lightness":16}]},{"elementType":"labels.text.fill","stylers":[{"saturation":36},{"color":"#333333"},{"lightness":40}]},{"elementType":"labels.icon","stylers":[{"visibility":"off"}]},{"featureType":"transit","elementType":"geometry","stylers":[{"color":"#f2f2f2"},{"lightness":19}]},{"featureType":"administrative","elementType":"geometry.fill","stylers":[{"color":"#fefefe"},{"lightness":20}]},{"featureType":"administrative","elementType":"geometry.stroke","stylers":[{"color":"#fefefe"},{"lightness":17},{"weight":1.2}]}];
            // Create a new StyledMapType object, passing it the array of styles,
            // as well as the name to be displayed on the map type control.
            var styledMap = new google.maps.StyledMapType(styles, {
                name: "Styled Map"
            });
            var myLatLng = new google.maps.LatLng(mapLat, mapLng);
            var mapOptions = {
                zoom: mapZoom,
                center: myLatLng,
                scrollwheel: false,
                panControl: false,
                zoomControl: true,
                scaleControl: false,
                mapTypeControl: false,
                streetViewControl: false,
                mapTypeControlOptions: {
                    mapTypeIds: [google.maps.MapTypeId.ROADMAP, 'map_style']
                }
            };
            map = new google.maps.Map(document.getElementById('map'), mapOptions);
            var marker = new google.maps.Marker({
                position: myLatLng,
                map: map,
                tittle: 'findmap',
                icon: 'img/icon/map_marker.png',
                animation: google.maps.Animation.DROP
            });
            map.mapTypes.set('map_style', styledMap);
            map.setMapTypeId('map_style');
        });

    }

    if ($('#map').length) {
        var map;
        google.maps.event.addDomListener(window, 'load', initialize_map);
    }


    // ******************************//
    // Testimonial Slider
    // ******************************//

    var swiper = new Swiper('.testimonial-carousel', {
        pagination: '.testimonial-pagination',
        paginationClickable: true
    });


    // ******************************//
    // Contact Form
    // ******************************//
    $('#contact-form').on('submit', function(e) {
        return form_to_ajax_request($(this), ['email', 'name', 'message'], ['email', 'name', 'message']);
    });
    function form_to_ajax_request(form_el, all_fields, required_fields) {
        var fields_values = [];
        var error = false;
        //get values from fields
        $.each(all_fields, function(index, value) {
            fields_values[value] = form_el.find('*[name=' + value + ']').val();
        });
        //check if required fields are set
        $.each(required_fields, function(index, value) {
            if (!isSet(fields_values[value])) {
                var message = form_el.data(value + '-not-set-msg');
                if (!isSet(message))
                    message = form_el.data('all-fields-required-msg');
                setReturnMessage(form_el, message);
                showReturnMessage(form_el);
                error = true;
                return;
            }
        });
        if (error)
            return false;

        //form data query object for ajax request
        var data_query = {};
        $.each(all_fields, function(index, value) {
            data_query[value] = fields_values[value];
        });
        data_query['ajax'] = true;

        //show ajax loader
        showLoader(form_el);

        //send the request
        $.ajax({
                type: form_el.attr('method'),
                url: form_el.attr('action'),
                data: data_query,
                cache: false,
                dataType: "text"
            })
            .fail(function() { //request failed
                setReturnMessage(form_el, form_el.data('ajax-fail-msg'));
                showReturnMessage(form_el);
            })
            .done(function(message) { //request succeeded
                if (!isSet(message)) {
                    clearForm(form_el);
                    setReturnMessage(form_el, form_el.data('success-msg'));
                    showReturnMessage(form_el);
                } else {
                    setReturnMessage(form_el, message);
                    showReturnMessage(form_el);
                }
            });
        //hide ajax loader
        hideLoader(form_el);
        return false;
    }

    function isSet(variable) {
        if (variable == "" || typeof(variable) == 'undefined')
            return false;
        return true;
    }
    function clearForm(form_el) {
        form_el.find('input[type=text]').val('');
        form_el.find('input[type=checkbox]').prop('checked', false);
        form_el.find('textarea').val('');
    }
    function showLoader(form_el) {
        form_el.find('.ajax-loader').fadeIn('fast');
    }
    function hideLoader(form_el) {
        form_el.find('.ajax-loader').fadeOut('fast');
    }
    function setReturnMessage(form_el, content) {
        if (!isSet(content))
            content = "Unspecified message.";
        form_el.find('.return-msg').html(content);
    }
    function showReturnMessage(form_el) {
        form_el.find('.return-msg').addClass('show-return-msg');
    }
    $('.return-msg').on('click', function(e) {
        $(this).removeClass('show-return-msg').html('');
    });

});

});