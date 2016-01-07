package org.cocos2dx.cpp;

import game.eswn.R;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Message;
import android.os.Handler;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;


public class SplashActivity extends Activity{

	 @Override
	    protected void onCreate(final Bundle savedInstanceState) {
	        super.onCreate(savedInstanceState);

	        setContentView(R.layout.activity_splash);	
	        
	        Handler h = new Handler();
	        h.postDelayed(new Runnable() {
	        	public void run() {
	        		finish();
	        		
	        		Intent intent = new Intent(SplashActivity.this, AppActivity.class);
	    	        startActivity(intent);
	    	        //overridePendingTransition(android.R.anim.slide_in_left,android.R.anim.slide_out_right);
	        	}
	        }, 1000);
	        
	    }
}
