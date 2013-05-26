<?php
header('Content-Type: text/html; charset=utf-8');

$langs = array();

if (isset($_SERVER['HTTP_ACCEPT_LANGUAGE'])) {
    // break up string into pieces (languages and q factors)
    preg_match_all('/([a-z]{1,8}(-[a-z]{1,8})?)\s*(;\s*q\s*=\s*(1|0\.[0-9]+))?/i', $_SERVER['HTTP_ACCEPT_LANGUAGE'], $lang_parse);

    if (count($lang_parse[1])) {
        // create a list like "en" => 0.8
        $langs = array_combine($lang_parse[1], $lang_parse[4]);
    	
        // set default to 1 for any without q factor
        foreach ($langs as $lang => $val) {
            if ($val === '') $langs[$lang] = 1;
        }

        // sort list based on value	
        arsort($langs, SORT_NUMERIC);
    }
}

// print page
if (empty($langs)) {
    $filecontents = file_get_contents("index.en.html");
} else {
    reset($langs);
    $lang = key($langs);
    
    if (strpos($lang, 'zh-cn') === 0) {
        $filecontents = file_get_contents("index.zh.cn.html");
	} else if (strpos($lang, 'zh-tw') === 0) {
		$filecontents = file_get_contents("index.zh.tw.html");
	} else if (strpos($lang, 'ru') === 0) {
		$filecontents = file_get_contents("index.ru.html");
	} else {
        $filecontents = file_get_contents("index.en.html");
    }
}
print $filecontents;  


// show default site or prompt for language
?>
