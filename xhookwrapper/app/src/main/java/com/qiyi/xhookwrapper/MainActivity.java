package com.qiyi.xhookwrapper;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import cn.shuzilm.core.Main;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView load = findViewById(R.id.load);

        load.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Main.init(MainActivity.this);
                com.qiyi.xhook.XHook.getInstance().refresh(false);
            }
        });

        findViewById(R.id.show).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                load.setText(Main.getQueryID(MainActivity.this));
                com.qiyi.xhook.XHook.getInstance().refresh(false);
            }
        });

        //load xhook
        com.qiyi.xhook.XHook.getInstance().init(this.getApplicationContext());
        if (!com.qiyi.xhook.XHook.getInstance().isInited()) {
            return;
        }
        //com.qiyi.xhook.XHook.getInstance().enableDebug(true); //default is false
        //com.qiyi.xhook.XHook.getInstance().enableSigSegvProtection(false); //default is true

        //load and run your biz lib (for register hook points)
        com.qiyi.biz.Biz.getInstance().init();
        com.qiyi.biz.Biz.getInstance().start();

        //xhook do refresh
        com.qiyi.xhook.XHook.getInstance().refresh(false);

        //load and run the target lib
//        com.qiyi.test.Test.getInstance().init();
//        com.qiyi.test.Test.getInstance().start();
//        try {
//            Thread.sleep(200);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }

        //xhook do refresh again
//        com.qiyi.xhook.XHook.getInstance().refresh(false);

        //xhook do refresh again for some reason,
        //maybe called after some System.loadLibrary() and System.load()
        //*
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true) {
                    com.qiyi.xhook.XHook.getInstance().refresh(true);

                    try {
                        Thread.sleep(5000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
        //*/
    }
}
