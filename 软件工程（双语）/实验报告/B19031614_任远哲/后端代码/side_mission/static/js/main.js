jQuery.noConflict()(function ($) {
	'use strict';
    $(document).on('ready',function() {
        function portfolio_item_gutter(){
            var $item = $('.portfolio-item-wrap'),
                $cont = $('.portfolio-masonry-wrapper'),
                $gut = parseInt($cont.attr('data-gutter')/2, 10);

                $cont.css({
                    'margin-left': -$gut +'px',
                    'margin-right': -$gut +'px'
                });

                $item.css({
                    'padding': $gut +'px'
                });

        }
        portfolio_item_gutter();
		
        function init_fancybox(){
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
        }
        function link_disable() {
            $('.classic-load-button').find('a').hide();
            $('.classic-load-button').find('p.end').show(200);

            setTimeout(function(){

                $('.classic-load-button').slideUp(400);

            },2500);
        }
        function inf_link_disable(){
           $('.infinite-load').slideDown(200);

           setTimeout(function(){

            $('.infinite-load').slideUp(400);

        },2500)
       }
	   
       function InfiniteScrolling() {
        var portfolio_offset = 0;
        if ($(window).scrollTop() + $(window).height() - 100 >= $infiniteContainer.offset().top + $infiniteContainer.height()) {
            $(window).off('scroll.infinite');
            $.ajax({
                dataType: 'html',
                msg     : '',
                type    : 'POST',
                url     : $('#infinite-load-link').prop('href'),
                success : function (data) {
                    var items  = $(data).filter('.portfolio-item-wrap'),
                    $data = $(data),
                    length = items.length,
                    html   = '';
                    if (length > 0) {
                        if (portfolio_offset !== length) {
                            for (var i = 0; portfolio_offset < length; portfolio_offset++, i++) {
                                html += items.eq(portfolio_offset).prop('outerHTML');
                            }

                            $('.portfolio-list').append(html);
                            $('.portfolio-list').imagesLoaded(function () {
                                $(window).trigger('resize');
                                $('.portfolio-list').isotope('reloadItems').isotope();
                            });
                            portfolio_item_gutter();
                            init_fancybox();

                            if (portfolio_offset == length) {
                                inf_link_disable();
                            }

                        } else {
                            inf_link_disable();
                        }
                    } else {
                        inf_link_disable();
                    }
                }
            });
        }
    }
	
    function load_more_classic() {
        var portfolio_offset = 0,
        portfolio_items_loaded = parseInt($('#classic-load-button-link').attr('data-load'), 10);
        $('#classic-load-button-link').on('click', function (e) {
            e.preventDefault();
            $.ajax({
                type : 'POST',
                url : $('#classic-load-button-link').attr('href'),
                dataType : 'html',
                msg : '',
                success : function (data) {
                    var items  = $(data).filter('.portfolio-item-wrap'),
                    length = items.length,
                    html   = '';
                    if (length > 0) {
                        if (portfolio_offset !== length) {
                            for (var i = 0; portfolio_offset < length && i < portfolio_items_loaded; portfolio_offset++, i++) {
                                html += items.eq(portfolio_offset).prop('outerHTML');
                            }


                            $('.portfolio-list').append(html);
                            $('.portfolio-list').imagesLoaded(function () {
                                $(window).trigger('resize');
                                $('.portfolio-list').isotope('reloadItems').isotope();
                            });
                            portfolio_item_gutter();
                            init_fancybox();


                            if (length <= portfolio_items_loaded || portfolio_offset == length) {
                                setTimeout(function(){
                                    link_disable();
                                },200);
                            }

                        } else {
                            setTimeout(function(){
                                link_disable();
                            },200);
                        }
                    } else {
                        setTimeout(function(){
                            link_disable();
                        },200);
                    }
                }
            });
        });
    }
    if ((typeof $.fn.imagesLoaded !== 'undefined') && (typeof $.fn.isotope !== 'undefined')) {
        if($('.infinite-load').length > 0) {
            $infinite = $('#infinite');
            $infiniteLink = $('#infinite-link');
            $infiniteContainer = $('.portfolio-list');
            $(window).on('scroll.infinite', InfiniteScrolling);
        }
        if($('.classic-load-button').length > 0) {

            load_more_classic();
        }
        var $container = $('.portfolio-list');
        $container.imagesLoaded(function() {
            $container.isotope({
                itemSelector: '.portfolio-item-wrap',
                layoutMode: 'masonry',
                transitionDuration: '0.8s'
            });
        });
        $('.filters-wrap a').on('click', function (e) {
            e.preventDefault();
            var $this = $(this);

            $('.filters-wrap a').removeClass('active');
            $(this).addClass('active');
            $container.isotope({
                filter: $(this).attr('data-filter')
            });

            return false;
        });
    }

});

});