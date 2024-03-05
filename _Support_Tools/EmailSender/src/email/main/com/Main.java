package email.main.com;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Properties;

import javax.activation.DataHandler;
import javax.activation.DataSource;
import javax.activation.FileDataSource;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class Main {

	static final int PARAMETER_ONE = 0;
	static final int PARAMETER_TWO = 1;
	static final int PARAMETER_THREE = 2;
	static final int PARAMETER_FOUR = 3;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String sSetup="";
		String sServer="";
		String sPort="";
	   	String sFrom;
	   	String sPwd;
	   	String sSubject="";
	   	String sBody="";
	    ArrayList<String> oAttachmentFiles=new ArrayList<String>();
	   	
	   	if(args.length == PARAMETER_ONE) {
	   		System.out.println("No Setup File");
	   		System.exit(0);
	   	} else if(args.length > PARAMETER_ONE) {
	   		sSetup=args[PARAMETER_ONE].trim();
	   	}
	   	
	   	if(args.length == PARAMETER_TWO) {
	   		System.out.println("No Subject Text");
	   		System.exit(0);
	   	} else if(args.length > PARAMETER_TWO) {
	   		sSubject=args[PARAMETER_TWO].trim();
	   	}
		
	   	if(args.length == PARAMETER_THREE) {
	   		System.out.println("No Body Text");
	   		System.exit(0);
	   	} else if(args.length > PARAMETER_THREE) {
	   		sBody=args[PARAMETER_THREE].replace("\\n", "\n").trim();
	   	}

	   	oAttachmentFiles.clear();
	   	if(args.length > PARAMETER_FOUR) {
	   		for(int nCount=3;nCount<args.length;nCount++) {
	   			oAttachmentFiles.add(args[nCount].trim());
	   		} 
	   	}
	   	
	   	JSONParser parser = new JSONParser();
		Object obj = null;
		try {
			obj = parser.parse(new FileReader(sSetup));
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
        JSONObject jsonScm = (JSONObject) jsonObject.get("Mail");
        
		sServer = (String) jsonScm.get("Server");
	   	sPort = (String) jsonScm.get("Port");
	   	sFrom = (String) jsonScm.get("From");
	   	sPwd = (String) jsonScm.get("Pwd");
	   	
	   	JSONArray jsonTo = (JSONArray) jsonScm.get("To");
	   	
	   	System.out.println(sSetup);
		System.out.println(sServer);
		System.out.println(sPort);
		System.out.println(sFrom);
		System.out.println(sPwd);
		System.out.println(sSubject);
		System.out.println(sBody);
		
   	    if(jsonTo!=null) {
  	  		@SuppressWarnings("rawtypes")
  	  		Iterator iteratorTo = jsonTo.iterator();
  	  		while (iteratorTo.hasNext()) {
  	  			JSONObject jsonEmail = (JSONObject) iteratorTo.next();
  	  			String sEmail = (String) jsonEmail.get("Email");
  	  		    System.out.println("Email " + sEmail);
  	  		}
   	  	}
		
        // Get system properties
        Properties properties = System.getProperties();

        // Setup mail server
        properties.put("mail.smtp.host", sServer);
        properties.put("mail.smtp.port", sPort);
        properties.put("mail.smtp.ssl.enable", "true");
        properties.put("mail.smtp.auth", "true");

        // Get the Session object.// and pass username and password
        Session session = Session.getInstance(properties, new javax.mail.Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication(sFrom, sPwd);
            }
        });

        // Used to debug SMTP issues
        session.setDebug(true);
        //session.setDebug(false);

        try {
            // Create a default MimeMessage object.
            MimeMessage message = new MimeMessage(session);

            // Set From: header field of the header.
            message.setFrom(new InternetAddress(sFrom));

     	  	if(jsonTo!=null) {
     	  		@SuppressWarnings("rawtypes")
     	  		Iterator iteratorTo = jsonTo.iterator();
     	  		while (iteratorTo.hasNext()) {
     	  			JSONObject jsonEmail = (JSONObject) iteratorTo.next();
     	  			String sEmail = (String) jsonEmail.get("Email");
     	  			message.addRecipient(Message.RecipientType.TO, new InternetAddress(sEmail));
     	  		}
     	   	}
     	  	  
            // Set Subject: header field
            message.setSubject(sSubject);

            // Create the message part
            BodyPart messageBodyPart = new MimeBodyPart();

            // Now set the actual message
            messageBodyPart.setText(sBody);            
            
            Multipart multipart = new MimeMultipart();
            
            // Set text message part
            multipart.addBodyPart(messageBodyPart);
            
     	  	if(oAttachmentFiles.size()>0) {
     	  	    for(int nCount=0;nCount<oAttachmentFiles.size();nCount++)  
                {  
     	  	    	MimeBodyPart attachPart = new MimeBodyPart();
     	            String attachFile = oAttachmentFiles.get(nCount);
     	            DataSource source = new FileDataSource(attachFile);
     	            attachPart.setDataHandler(new DataHandler(source));
     	            attachPart.setFileName(new File(attachFile).getName());
     	            multipart.addBodyPart(attachPart);
                }  
     	  	}
    
     	  	message.setContent(multipart);
            
            System.out.println("sending...");
            // Send message
            Transport.send(message);
            System.out.println("Sent message successfully....");
        } catch (MessagingException mex) {
            mex.printStackTrace();
        }

	}
}
