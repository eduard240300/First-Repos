<?php

include_once("controller.php");
$controller = new Controller();

$aResult = array();

    if( !isset($_POST['functionname']) ) { $aResult['error'] = 'No function name!'; }

    if( !isset($_POST['arguments']) ) { $aResult['error'] = 'No function arguments!'; }

    if( !isset($aResult['error']) ) {

        switch($_POST['functionname']) {
            case 'addToShoppingCart':
               if( !is_array($_POST['arguments']) || (count($_POST['arguments']) != 1) ) {
                   $aResult['error'] = 'Error in arguments!';
               }
               else {
                   $controller->addToShoppingCart($_POST['arguments'][0]);
               }
               break;

            case 'removeFromShoppingCart':
                if( !is_array($_POST['arguments']) || (count($_POST['arguments']) != 1) ) {
                    $aResult['error'] = 'Error in arguments!';
                }
                else {
                    $controller->removeFromShoppingCart($_POST['arguments'][0]);
                }
                break;
            
            default:
               $aResult['error'] = 'Not found function '.$_POST['functionname'].'!';
               break;
        }

    }

    echo json_encode($aResult);

?>