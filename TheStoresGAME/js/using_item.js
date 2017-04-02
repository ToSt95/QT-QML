function use_item(item_id,url)
{
    if(item_id.in_eq == true && item_id.position == 1 )
    {

        c_s1 = "transparent"
        i_s1 = true
        item_id.in_eq = false
        item_id.used = true
        t1.aaa = url
        t1.start()
        fade_in.start()
        next.play()

    }

    else   if(item_id.in_eq == true && item_id.position == 2)
    {
        c_s2 = "transparent"

        item_id.in_eq = false

        i_s2 = true



        t1.aaa = url
        t1.start()
        fade_in.start()
        next.play()
        item_id.used = true
    }
    else if(item_id.in_eq == true && item_id.position == 3 )
    {
        c_s3 = "transparent"

        item_id.in_eq = false

        i_s3 = true



        t1.aaa = url
        t1.start()
        fade_in.start()
        next.play()
        item_id.used = true
    }
    else if(item_id.in_eq == true && item_id.position == 4)
    {
        c_s4 = "transparent"

        item_id.in_eq = false

        i_s4 = true



        t1.aaa = url
        t1.start()
        fade_in.start()
        next.play()
        item_id.used = true
    }
    else if(item_id.used == true)
    {

        t1.aaa = url
        t1.start()
        fade_in.start()
        next.play()

    }
}
