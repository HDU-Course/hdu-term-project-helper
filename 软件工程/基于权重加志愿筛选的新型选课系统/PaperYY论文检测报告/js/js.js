$(function () {
    var WinH = $(window).height();
    var H = WinH-$('.header').height();
    $('.overflow-auto').height(H);
    $(window).resize(function () {
        WinH = $(window).height();
        H = WinH-$('.header').height();
        $('.overflow-auto').height(H)
    });


    $('#nav span').click(function () {
        $('#nav span').toggleClass('active');
        $('#content .cont-li').toggleClass('active');
    })
})