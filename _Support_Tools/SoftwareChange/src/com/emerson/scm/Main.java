package com.emerson.scm;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import com.emerson.tools.Console;
import com.emerson.tools.Jazz;
import com.emerson.tools.WindowsProcessKiller;

public class Main {
	
	private static final String SCM_COMMAND_ERROR = "Problem running";	
	private static final String SCM_FILENAME_RESULT = "Result.txt";	
	private static final String SCM_FILENAME_BASELINE = "Baseline.txt";	
	private static final String SCM_FILENAME_STREAM = "Stream.txt";
	private static final String SCM_FILENAME_WORKSPACE = "Workspace.txt";
	private static final String SCM_FILENAME_WORKSPACE_UUID = "Workspace_UUID.txt";
	private static final String SCM_FILENAME_SERVER = "Server.txt";
  
	private ArrayList<String> cmds;	
	private Console consoleWorkspace;
	private boolean fail;
	private String ConfigFile = null;
	  
	public void setConfig(String AConfig) {
		this.ConfigFile = AConfig.trim();
	}
	
	public void WriteFile(String AFileName,String AValue) {
		try {
	  		File file = new File(AFileName);
	  		if(file.delete()) {}
		}
	    catch (Exception e) {
	  		e.printStackTrace();
	  	}	
	  	try {
	  		FileWriter writer = new FileWriter(AFileName, true);
	  		writer.write(AValue);
	  		writer.close();
	  	} catch (IOException e) {
	  		e.printStackTrace();
	  	}		
	}
	
	public void run() {
		String sJasonResult = null;
		String sBaseLine = null;
		String sStream = null;
		String sWorkSpace = null;
		String sWorkSpaceUUID = null;
		String sServer = null;
		int nSoftwareChange = 0;
		
  	  	this.cmds = new ArrayList<String>();
		// get the json parameters
		JSONParser parser = new JSONParser();
		Object obj = null;
		try {
			obj = parser.parse(new FileReader(this.ConfigFile));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        JSONObject jsonObject = (JSONObject) obj;
        JSONObject jsonScm = (JSONObject) jsonObject.get("Scm");
        
        String cfg_alias = (String) jsonScm.get("Alias");
        String scm_server = (String) jsonScm.get("Server");
        String scm_user = (String) jsonScm.get("User");
        String scm_pwd = (String) jsonScm.get("Pwd");
        String scm_workspace = (String) jsonScm.get("Workspace");
        
        JSONArray jsonProjects = (JSONArray) jsonScm.get("Projects");
        JSONArray jsonFiles = (JSONArray) jsonScm.get("Files");

        System.out.println("scm_server: " + scm_server);
        System.out.println("scm_user: " + scm_user);
        ////////////////////////////////////////////////
        // System.out.println("scm_pwd: " + scm_pwd); //
        ////////////////////////////////////////////////
        System.out.println("scm_workspace: " + scm_workspace);
        
  	  	this.consoleWorkspace = new Console(scm_workspace);
        
  	  	this.fail = false;
  	  	this.cmds.clear();
  	  	this.cmds.add("scm"); 
  	  	this.cmds.add("login");
  	  	this.cmds.add("-r"); 
  	  	this.cmds.add(scm_server);
  	  	this.cmds.add("-u");
  	  	this.cmds.add(scm_user);
  	  	this.cmds.add("-P"); 
  	  	this.cmds.add(scm_pwd);
  	  	this.cmds.add("-n"); 
  	  	this.cmds.add("Jazz");
  	  	System.out.println(this.cmds.toString());
  	  	this.consoleWorkspace.commands(this.cmds);
  	  	this.consoleWorkspace.showOutput();
  	  	this.fail = this.consoleWorkspace.isFoundString(SCM_COMMAND_ERROR);
  	  	
  	  	if(!this.fail) {
  	  		
  		  this.cmds.clear();
  		  this.cmds.add("scm");
  		  this.cmds.add("show");
  		  this.cmds.add("status");
  		  this.cmds.add("--json");
  		  System.out.println(this.cmds.toString());
  		  this.consoleWorkspace.commands(this.cmds);
  		  this.consoleWorkspace.showOutput();
  		  this.fail = this.consoleWorkspace.isFoundString(SCM_COMMAND_ERROR);
  		  
  		  if(!this.fail) {
  			  sJasonResult = "";
  			  for (int Count=0;Count<this.consoleWorkspace.getResult().size();Count++) {
  				  sJasonResult+=this.consoleWorkspace.getResult().get(Count).trim();
  			  }
  			  Jazz jazz = new Jazz(sJasonResult);
  			  sBaseLine = jazz.getBaseLine();
  			  sStream = jazz.getStream();
  			  sWorkSpace = jazz.getWorkSpace();
  			  sWorkSpaceUUID = jazz.getWorkSpaceUUID();
  			  sServer = jazz.getServer();
  			  
  			  // create result files for each projects
  	   	  	  if(jsonProjects!=null) {
  	  	  		@SuppressWarnings("rawtypes")
  	  	  		Iterator iteratorProjects = jsonProjects.iterator();
  	  	  		while (iteratorProjects.hasNext()) {
  	  	  			JSONObject jsonProject = (JSONObject) iteratorProjects.next();
  	  	  			String sProject = (String) jsonProject.get("Project");
  	  	  		    int nProjectChange = 0;
  	  	  		    nProjectChange = jazz.getSoftwareChangeProject(sProject);
  	  	  		    if(nProjectChange>0)nSoftwareChange = nProjectChange;
  	  	  		    System.out.println("Incoming for "+sProject+": " + nProjectChange);
  	  	  		    WriteFile(cfg_alias+"_"+sProject+".txt",""+nProjectChange);
  	  	  		    String sUUID=jazz.getProjectUUID(sProject);
  	  	  		    WriteFile(cfg_alias+"_"+sProject+"_UUID.txt",sUUID);
  	  	  		
  	  	  		}
  	  	  		@SuppressWarnings("rawtypes")
  	  	  		Iterator iteratorFiles = jsonFiles.iterator();
  	  	  		while (iteratorFiles.hasNext()) {
  	  	  			JSONObject jsonFile = (JSONObject) iteratorFiles.next();
  	  	  			String sFile = (String) jsonFile.get("File");
  	  	  		    //int nFileChange = jazz.getSoftwareChangeFile(sFile);
  	  	  		    int nFileChange = jazz.getSoftwareUnresolvedFile(sFile);
  	  	  		    System.out.println("Outgoing for "+sFile+": " + nFileChange);
  	  	  		    WriteFile(cfg_alias+"_"+sFile+".txt",""+nFileChange);
  	  	  		}
  	  	  	  }
  	   	  	  
  	   	  	  // result for a change
  	  		  WriteFile(cfg_alias+"_"+SCM_FILENAME_RESULT,""+""+nSoftwareChange);
  	  		  WriteFile(cfg_alias+"_"+SCM_FILENAME_BASELINE,sBaseLine.trim());
  	  		  WriteFile(cfg_alias+"_"+SCM_FILENAME_STREAM,sStream.trim());
  	  		  WriteFile(cfg_alias+"_"+SCM_FILENAME_WORKSPACE,sWorkSpace.trim());
  	  	      WriteFile(cfg_alias+"_"+SCM_FILENAME_WORKSPACE_UUID,sWorkSpaceUUID.trim());
  	  	      WriteFile(cfg_alias+"_"+SCM_FILENAME_SERVER,sServer.trim());
  		  }
  	  		
  		  this.cmds.clear();
  		  this.cmds.add("scm");
  		  this.cmds.add("logout");
  		  this.cmds.add("--repository-uri");
  		  this.cmds.add("Jazz");
  		  System.out.println(this.cmds.toString());
  		  this.consoleWorkspace.commands(this.cmds);
  		  this.consoleWorkspace.showOutput();
 	  	}
  	  	
  	  	if(this.fail) nSoftwareChange = -1;
  	  	
  	  	System.out.println("Change: " + nSoftwareChange);
  	    System.out.println("BaseLine: " + sBaseLine);
  	    System.out.println("Stream: " + sStream);
  	    System.out.println("WorkSpace: " + sWorkSpace);
  	    System.out.println("Server: " + sServer);
	}
	

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Main main = new Main();

		//WindowsProcessKiller pKiller = new WindowsProcessKiller();

		//String processName = "wrwb.exe";
		//boolean isRunning = pKiller.isProcessRunning(processName);

		//System.out.println("is " + processName + " running : " + isRunning);

		//if (isRunning) {
		//	WindowsProcessKiller.killProcess(processName);
		//}
		
		if (args.length > 0) {
			main.setConfig(args[0]);
			main.run();
		}
		else
		{
			System.out.println("Need json configuration file!");	
		}
		
       	
 	}

}
