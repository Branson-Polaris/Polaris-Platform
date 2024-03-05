package com.emerson.tools;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Iterator;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class Jazz {
	
	public Object Obj = null;
	public JSONObject JsonObject = null;
	
	public Jazz(String ScmStatus) {
		JSONParser parser = new JSONParser();
		try {
			this.Obj = parser.parse(ScmStatus);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        JsonObject = (JSONObject) this.Obj;
	}
	
	public int getSoftwareChangeProject(String Project) {
		int nResult = 0;
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        JSONArray jsonComponents = (JSONArray) jsonWorkspace.get("components");
        JSONObject jsonComponent = null;
        if(jsonComponents!=null) {
        	@SuppressWarnings("rawtypes")
        	Iterator iteratorComponents = jsonComponents.iterator();
        	while (iteratorComponents.hasNext()) {
        		jsonComponent = (JSONObject) iteratorComponents.next();
        		String sComponentName = (String) jsonComponent.get("name");
        		if(Project.equals(sComponentName.trim()) || Project.equals("")) {
        	       if(jsonComponent!=null) {
        	        	JSONArray jsonIncomingChanges = (JSONArray) jsonComponent.get("incoming-changes");
        	        	if(jsonIncomingChanges!=null) {
        	        		@SuppressWarnings("rawtypes")
        	        		Iterator iteratorChanges = jsonIncomingChanges.iterator();
        	        		while (iteratorChanges.hasNext()) {
        	        			JSONObject jsonChanges = (JSONObject) iteratorChanges.next();
        	        			JSONArray jsonChangesChanges = (JSONArray) jsonChanges.get("changes");
        	        			if(jsonChangesChanges.size()>0) nResult = 1;
        	        		}
        	        	}
        	        }
        		}
        	}
        }
        return nResult;
	}
	
	public int getSoftwareChangeFile(String AFile) {
		int nResult = 0;
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        JSONArray jsonComponents = (JSONArray) jsonWorkspace.get("components");
        JSONObject jsonComponent = null;
        if(jsonComponents!=null) {
        	@SuppressWarnings("rawtypes")
        	Iterator iteratorComponents = jsonComponents.iterator();
        	while (iteratorComponents.hasNext()) {
        		jsonComponent = (JSONObject) iteratorComponents.next();
        	       if(jsonComponent!=null) {
        	        	JSONArray jsonIncomingChanges = (JSONArray) jsonComponent.get("outgoing-changes");
        	        	if(jsonIncomingChanges!=null) {
        	        		@SuppressWarnings("rawtypes")
        	        		Iterator iteratorChanges = jsonIncomingChanges.iterator();
        	        		while (iteratorChanges.hasNext()) {
        	        			JSONObject jsonChanges = (JSONObject) iteratorChanges.next();
        	        			JSONArray jsonChangesChanges = (JSONArray) jsonChanges.get("changes");
        	       	        	if(jsonChangesChanges!=null) {
                	        		@SuppressWarnings("rawtypes")
                	        		Iterator iteratorChangesChanges = jsonChangesChanges.iterator();
                	        		while (iteratorChangesChanges.hasNext()) {
                	        			JSONObject jsonItemChangesChanges = (JSONObject) iteratorChangesChanges.next();
                	        			String sPath = (String) jsonItemChangesChanges.get("path");
                	        			Path p = Paths.get(sPath);
                	        			String sFileName = p.getFileName().toString();
                	        			if(AFile.equals(sFileName.trim())) {
                	        				nResult = 1;
                	        				break;
                	        			}
                	            		//System.out.println("");
                	        			//System.out.println("FileName: " + sFileName + " " + AFile);
                 	        		}
        	       	        	}
        	       	        	if(nResult == 1)break;
        	        		}
        	        	}
        	        }
        	}
        }
        return nResult;
	}
	
	public int getSoftwareUnresolvedFile(String AFile) {
		int nResult = 0;
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        JSONArray jsonComponents = (JSONArray) jsonWorkspace.get("components");
        JSONObject jsonComponent = null;
        if(jsonComponents!=null) {
        	@SuppressWarnings("rawtypes")
        	Iterator iteratorComponents = jsonComponents.iterator();
        	while (iteratorComponents.hasNext()) {
        		jsonComponent = (JSONObject) iteratorComponents.next();
        	       if(jsonComponent!=null) {
        	        	JSONArray jsonIncomingChanges = (JSONArray) jsonComponent.get("unresolved");
        	        	if(jsonIncomingChanges!=null) {
        	        		@SuppressWarnings("rawtypes")
        	        		Iterator iteratorChanges = jsonIncomingChanges.iterator();
        	        		while (iteratorChanges.hasNext()) {
        	        			JSONObject jsonChanges = (JSONObject) iteratorChanges.next();

        	        			String sPath = (String) jsonChanges.get("path");
        	        			Path p = Paths.get(sPath);
        	        			String sFileName = p.getFileName().toString();
        	        			if(AFile.equals(sFileName.trim())) {
        	        				nResult = 1;
        	        				break;
        	        			}
        	            		//System.out.println("");
        	        			//System.out.println("FileName: " + sFileName + " " + AFile);
        	       	        	
        	        		}
        	        	}
        	        }
        	}
        }
        return nResult;
	}
	
	public String getBaseLine() {
		String sResult = null;
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        JSONArray jsonComponents = (JSONArray) jsonWorkspace.get("components");
        JSONObject jsonComponent = null;
        if(jsonComponents!=null) {
        	@SuppressWarnings("rawtypes")
        	Iterator iteratorComponents = jsonComponents.iterator();
        	while (iteratorComponents.hasNext()) {
        		jsonComponent = (JSONObject) iteratorComponents.next();
        		//String sComponentName = (String) jsonComponent.get("name");
        		JSONObject jsonBaseline = (JSONObject) jsonComponent.get("baseline");
        		String sBaseline = (String) jsonBaseline.get("name");
        		sResult = sBaseline;
        		//System.out.println("");
    			//System.out.println("name: " + sComponentName);
    			//System.out.println("base: " + sBaseline);
        		break;
         	}
        }
        return sResult;
	}
	
	public String getStream() {
		String sResult = null;
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        JSONObject jsonFlowTarget = (JSONObject) jsonWorkspace.get("flow-target");
        sResult = (String) jsonFlowTarget.get("name");
        return sResult;
	}
	
	public String getWorkSpace() {
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        return (String) jsonWorkspace.get("name");
	}
	
	public String getWorkSpaceUUID() {
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        return (String) jsonWorkspace.get("uuid");
	}
	
	public String getServer() {
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        return (String) jsonWorkspace.get("url");
	}
	
	public String getProjectUUID(String Project) {
		String sResult = null;
		JSONArray jsonWorkspaces = (JSONArray) this.JsonObject.get("workspaces");
        JSONObject jsonWorkspace = (JSONObject) jsonWorkspaces.get(0);       
        JSONArray jsonComponents = (JSONArray) jsonWorkspace.get("components");
        JSONObject jsonComponent = null;
        if(jsonComponents!=null) {
        	@SuppressWarnings("rawtypes")
        	Iterator iteratorComponents = jsonComponents.iterator();
        	while (iteratorComponents.hasNext()) {
        		jsonComponent = (JSONObject) iteratorComponents.next();
        		String sComponentName = (String) jsonComponent.get("name");
        		if(Project.equals(sComponentName.trim()) || Project.equals("")) {
        	       if(jsonComponent!=null) {
        	    	    sResult = (String) jsonComponent.get("uuid");
        	        }
        		}
        	}
        }
        return sResult;
	}

}
