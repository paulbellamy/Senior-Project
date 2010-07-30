<?php
  session_start();
  
  if (isset($_POST['repeat'])) {
    $_SESSION['data'] = $_POST['data'];
    $_SESSION['answer'] = $_POST['answer'];
    header("Location: ask.php");
    exit();
  }
  
  if (isset($_POST['data'])) {
    if (trim(strtoupper($_POST['data'])) == trim(strtoupper($_POST['answer']))) {
      $_SESSION['correct']++;
      $correct = true;
    }
    
    $_SESSION['answered']++;
  }
?>
<html>
  <head></head>
  <body onLoad="document.getElementById('next-button').focus()">
    <form action="ask.php" method="POST">
      <?php
        if ($correct) {
          echo 'Correct!';
        } else {
          echo 'Incorrect! Answer is: ',$_POST['data'];
        }
      ?>
      <br />
      <?php echo $_SESSION['correct'],' / ',$_SESSION['answered'],' correct.'; ?>
      <br /><br />
      <input type="submit" name="submit" value="Restart" />&nbsp;<input type="submit" id="next-button" name="submit" value="Next" />
    </form>
  </body>
</html>
