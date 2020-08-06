package Comunicacion;


import Logica.Tablero;

public class Cliente extends comunicacion {

    public  java.lang.String array;
    public  java.lang.String msj;


    public String getArray() {
        return array;
    }

    public void setArray(String array) {
        this.array = array;
    }

    public Cliente() throws java.io.IOException{
        super("cliente");
    }

    public String getMsj() {
        return msj;
    }

    public void setMsj(String msj) {
        this.msj = msj;
    }

    public void initClient(){
        try {
            msjOut = new java.io.DataOutputStream(client.getOutputStream());
            msjOut.writeBytes(msj);
            //System.out.println("msjSent");

            java.io.BufferedReader inFromServer = new java.io.BufferedReader(new java.io.InputStreamReader(client.getInputStream()));
            java.lang.String reply = inFromServer.readLine();
            setArray(ProcessServerInput.read(reply));
            client.close();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }

    }
}
