<?php 
		if (function_exists('connect')){

		} else {

		function connect(){	

				$user = getenv('CLOUDSQL_USER');
				$pass = getenv('CLOUDSQL_PASSWORD');
				$inst = getenv('CLOUDSQL_DSN');
				$db = getenv('CLOUDSQL_DB');
				$link = mysqli_connect(null, $user, $pass, $db, null, $inst);
				/*$now = new DateTime();
				$mins = $now->getOffset() / 60;
				$sgn = ($mins < 0 ? -1 : 1);
				$mins = abs($mins);
				$hrs = floor($mins / 60);
				$mins -= $hrs * 60;
				$offset = sprintf('%+d:%02d', $hrs*$sgn, $mins);
				$connection->query("SET time_zone='$offset'");
			    $connection->query("SET lc_time_names = 'ro_RO'");*/
			
				if (!$link) {
						echo "Error!".mysqli_connect_error();
					}
				
				return $link;
		}
		}

		
?>