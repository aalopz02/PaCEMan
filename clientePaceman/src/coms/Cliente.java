package coms;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Cliente extends comunicacion{

    public Cliente() throws IOException{
        super("cliente");
    }

    public void initClient(){
        try {
            msjOut = new DataOutputStream(client.getOutputStream());
            msjOut.writeInt(1);
            BufferedReader inFromServer = new BufferedReader(new InputStreamReader(client.getInputStream()));
            System.out.println("msjSent");
            System.out.println(inFromServer.readLine());
            client.close();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }

    }
}