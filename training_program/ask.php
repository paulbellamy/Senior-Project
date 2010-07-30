<?php
  session_start();
  
  if ($_POST['submit'] == "Begin") {
    $_SESSION['answered'] = 0;
    $_SESSION['correct'] = 0;
    $_SESSION['type'] = $_POST['type'];
    $_SESSION['koch_size'] = (int)$_POST['koch_size'];
  } else if ($_POST['submit'] == "Restart") {
    header('Location: index.php');
    exit;
  }
  
  require_once("dictionary.inc.php");

  if (isset($_POST['data']) && $_POST['data']) {
    $data = $_POST['data'];
  } else if (isset($_SESSION['data']) && $_SESSION['data']) {
    $data = $_SESSION['data'];
    $_SESSION['data'] = null;
  }

  if (!$data) {
    // Pick the word/letter
    if ($_SESSION['type'] == "Words") {
      $data = getWord();
    } else if ($_SESSION['type'] == "Letters") {
      $data = getLetter();
    } else if ($_SESSION['type'] == "Sentences") {
      $data = getSentence(rand(1, 6));
    } else if ($_SESSION['type'] == "Koch Method") {
      $data = getKochSentence($_SESSION['koch_size'], rand(1,6));
    }
  }
?>
<html>
  <head></head>
  <body onLoad="document.getElementById('answer').focus()">
    <?php
      // Send data to arduino if available
      $ch = curl_init('http://192.168.1.86/training?p=pa55word&d='.$data);
      
      //curl_setopt($ch, CURLOPT_HEADER, 0);
      curl_setopt($ch, CUROPT_RETURNTRANSFER, 1);
      
      $result = curl_exec($ch);
      curl_close($ch);
      
      /* FIXME: This makes it always work, regardless of it reaching the device */
      $result = "hi";
      
      if ($result) {
        ?>
          <form action="answer.php" method="POST" name="form">
            <input type="hidden" name="data" value="<?php echo $data; ?>" />
            Data: <b style="color:#ffffff;"><?php echo $data; ?></b><br />
            <input type="text" id="answer" name="answer"
              <?php
                if (isset($_SESSION['answer'])) {
                  echo 'value="',$_SESSION['answer'],'"';
                  $_SESSION['answer'] = null;
                }
              ?>
            />
            <br /><br />
            <input type="submit" name="submit" value="Answer" />
	    <input type="submit" name="repeat" value="Repeat" />
          </form>
        <?php
      } else {
        //Couldn't reach arduino
        ?>
          <form action="ask.php" method="POST">
            <div style="color:#FF0000;">Could not connect to the device.</div>
            <br />
            <input type="submit" name="submit" value="Try Again" />
          </form>
        <?php
      }
    ?>
  </body>
</html>
