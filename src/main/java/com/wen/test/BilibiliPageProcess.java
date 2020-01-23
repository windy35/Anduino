package com.wen.test;

import com.alibaba.fastjson.JSONObject;
import us.codecraft.webmagic.Page;
import us.codecraft.webmagic.Site;
import us.codecraft.webmagic.Spider;
import us.codecraft.webmagic.processor.PageProcessor;
import us.codecraft.webmagic.selector.Json;
import org.springframework.core.io.ClassPathResource;
import org.springframework.core.io.Resource;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class BilibiliPageProcess implements PageProcessor {

    public void TextToFile(final String strFilename, final String strBuffer)
    {
        try
        {
            // 创建文件对象
            File fileText = new File(strFilename);
            // 向文件写入对象写入信息
            FileWriter fileWriter = new FileWriter(fileText);
            // 写文件
            fileWriter.write(strBuffer);
            // 关闭
            fileWriter.close();
        }
        catch (IOException e)
        {
            //
            e.printStackTrace();
        }
    }


    private Site site = Site.me()
            .setRetrySleepTime(3);
    //.addHeader("Cookie", "sid=73z7tai9; fts=1499404833; pgv_pvi=4286189568; LIVE_BUVID=038be0e7dbefae118807a05ce6758c31; LIVE_BUVID__ckMd5=35b7fa0ba25cd9c6; rpdid=iwpsxqxxqxdopllxpxipw; buvid3=6ECE81DC-0F17-4805-A8D8-93AAA590623537243infoc; biliMzIsnew=1; biliMzTs=0; UM_distinctid=160c4c3cad640-0317802b275f19-5a442916-144000-160c4c3cad724e; im_notify_type_1393013=0; _cnt_dyn=undefined; _cnt_pm=0; _cnt_notify=0; uTZ=-480; CURRENT_QUALITY=64; im_local_unread_1393013=0; im_seqno_1393013=37; finger=edc6ecda; DedeUserID=1393013; DedeUserID__ckMd5=afb19007fffe33b0; SESSDATA=0ea7d6d3%2C1531986297%2C72337142; bili_jct=1814a4be6409416a0cc9f606e5494a09; _dfcaptcha=bebbef520c7c46f8cb0a877c33c677e1; bp_t_offset_1393013=132005944396809066")
    //.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.87 Safari/537.36");

    @Override
    public Site getSite() {
        return this.site;
    }

    @Override
    public void process(Page page) {
        Json result = page.getJson();
        JSONObject jsonObject = JSONObject.parseObject(result.toString());
        JSONObject data = jsonObject.getJSONObject("data");
        JSONObject card = data.getJSONObject("card");
        String fans = card.getString("fans"); // 粉丝数
        String attention = card.getString("attention"); // 关注数
        System.out.println("粉丝数："+fans);
        System.out.println("关注数："+attention);
        //用于获取项目路径
        Resource resource = new ClassPathResource("");
        try {
            //将粉丝数据保存在项目的 getfans\target\classes\Files\1.txt 文件下
            TextToFile(resource.getFile().getAbsolutePath()+"\\Files\\1.txt",fans);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String bilibiliId="14572224";
        String url = "https://api.bilibili.com/x/web-interface/card?mid=" + bilibiliId;
        Spider.create(new BilibiliPageProcess())
                .addUrl(url)
                .thread(1)
                .run();
    }

}
