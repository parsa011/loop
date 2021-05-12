<?php
function xor_encrypt($in) {
    $key = 'qw8J';
    $text = $in;
    $outText = '';

    // Iterate through each character
    for($i=0;$i<strlen($text);$i++) {
    $outText .= $text[$i] ^ $key[$i % strlen($key)];
    }

    return $outText;
}

$data= $arrayName = array('showpassword' => 'yes', 'bgcolor'=>'#0f00f0');
echo base64_encode(xor_encrypt(json_encode($data)));
?>