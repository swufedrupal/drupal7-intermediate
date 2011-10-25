<?php

/**
 *  @file
 *  Create a YouKu Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $youku = new ResourceYouKuStreamWrapper('youku://?v=[video-code]');
 */
class MediaYouKuStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://youku.com/watch';

  function getTarget($f) {
    return FALSE;
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/youku';
  }

  function getOriginalThumbnailPath() {
    $parts = $this->get_parameters();
    $link = 'http://v.youku.com/v_show/id_'. check_plain($parts['v']) .'=.html';
    $content = file_get_contents($link);
    preg_match_all("/\+0800\|(.*?)\|\">/i",$content,$img);
    $img[1][0] = str_replace("ykimg.com/0", "ykimg.com/1", $img[1][0]);
    return $img[1][0];
    
  }

  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = 'public://media-youku/' . check_plain($parts['v']) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      @copy($this->getOriginalThumbnailPath(), $local_path);
    }
    return $local_path;
  }
}
