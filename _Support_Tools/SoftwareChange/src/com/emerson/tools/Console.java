package com.emerson.tools;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Console {
	
	public static final String FILE_LOG = "log.txt";
	public static final DateFormat sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
	
	private ArrayList<String> Result;
	private String WorkingDirectory;

	public Console(String workDir) {
		this.WorkingDirectory = workDir;
		this.Result = new ArrayList<String>();
	}
	
	public ArrayList<String> getResult() {
		return this.Result;
	}

	public void commands(ArrayList<String> cmds) {
	     ProcessBuilder pb = new ProcessBuilder(cmds); 
	     pb.redirectErrorStream(true);
	     pb.directory(new File(this.WorkingDirectory));
	     this.Result.clear();
         // startinf the process 
	     Process process = null;
		 try {
			process = pb.start();
		 } catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		 } 
	     // for reading the ouput from stream 
	     BufferedReader stdInput = new BufferedReader(new
	     InputStreamReader(process.getInputStream())); 
	     String s = null; 
	     try {
			while ((s = stdInput.readLine()) != null) 
		    { 
				this.Result.add(s);
			}
		 } catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		 } 
	}

	public boolean isFoundString(String textWord)
	{
		boolean bFail=false;
		for (int Count=0;Count<this.Result.size();Count++) {
		  bFail = this.Result.get(Count).trim().contains(textWord.trim());
 		  if(bFail==true){ 
			  break;
		  }
		}
		return bFail;
	}
	
	public void readFile(String fileRead) {
		File file = new File(fileRead); 
	    BufferedReader br = null;
	    String s;
	    this.Result.clear();
		try {
			br = new BufferedReader(new FileReader(file));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		try {
			while ((s = br.readLine()) != null) { 
			    this.Result.add(s);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
	
	public void showOutput() {
	  for (int Count=0;Count<this.Result.size();Count++) {
		 System.out.println(this.Result.get(Count).trim());
 	  }
	}
	
	public void saveResult() {
		try {
            FileWriter writer = new FileWriter(FILE_LOG, true);
      	    for (int Count=0;Count<this.Result.size();Count++) {
      	    	writer.write(sdf.format(new Date())+" "+this.Result.get(Count).trim());
      	    	writer.write("\r\n"); // write new line
      	    }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }	
	}
	
	public static void saveLine(String line) {
		try {
            FileWriter writer = new FileWriter(FILE_LOG, true);
      	    writer.write(sdf.format(new Date())+" "+line.trim());
      	    writer.write("\r\n"); // write new line
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }	
	}	
	
	public static boolean deleteLog() {
		boolean isDeleted = false;
		try {
            File file = new File(FILE_LOG);
            if(file.delete()) isDeleted = true;
        } catch (Exception e) {
            e.printStackTrace();
        }	
		return isDeleted;
	}
	
	protected void finalize ()  {
		this.Result.clear();
		this.Result = null;
	}
	
	public static void copyDirectory(String sourceLocation, String targetLocation) {

		File sourceFile = new File(sourceLocation);
		File destinationFile = new File(targetLocation);

		FileInputStream fileInputStream = null;
		try {
			fileInputStream = new FileInputStream(sourceFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		FileOutputStream fileOutputStream = null;
		try {
			fileOutputStream = new FileOutputStream(destinationFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		int bufferSize;
		byte[] bufffer = new byte[1024];
		try {
			while ((bufferSize = fileInputStream.read(bufffer)) > 0) {
			    fileOutputStream.write(bufffer, 0, bufferSize);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			fileInputStream.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			fileOutputStream.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	public static boolean delDirectory(File dir) {
	      if (dir.isDirectory()) {
	         String[] children = dir.list();
	         for (int i = 0; i < children.length; i++) {
	            boolean success = delDirectory (new File(dir, children[i]));
	            if (!success) {
	               return false;
	            }
	         }
	      }
	      return dir.delete();
	 }
}
