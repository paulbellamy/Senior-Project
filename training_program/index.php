<?php
  session_start();
?>
<html>
  <head></head>
  <body>
    <form action="ask.php" method="POST">
      Train On:<br />
      <input type="radio" name="type" value="Letters" checked /> Letters
      <br />
      <input type="radio" name="type" value="Words" /> Words
      <br />
      <input type="radio" name="type" value="Sentences" /> Sentences
      <br />
      <input type="radio" name="type" value="Koch Method" /> Koch Method ->
      Size:
        <select name="koch_size">
          <?php
            for ($i=2; $i <= 40; $i++) {
              echo '<option value="',$i,'" /> ',$i,"\n";
            }
          ?>
        </select>
      <br /><br />
      <input type="submit" name="submit" value="Begin" />
    </form>
  </body>
</html>
