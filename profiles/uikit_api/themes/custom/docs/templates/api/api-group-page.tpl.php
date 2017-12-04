<?php

/**
 * @file
 * Displays an API page for a topic/group, with list of items in that group.
 *
 * Available variables:
 * - $alternatives: List of alternate versions (branches) of this group.
 * - $documentation: Documentation from the comment header of the constant.
 * - $see: Related API objects.
 * - $related_topics: Related topics documentation.
 * - $objects: Formatted list of member objects, if any.
 * - $defined: HTML reference to file that defines this group.
 *
 * @ingroup themeable
 */
?>

<div id="docs-api">
  <?php if (!empty($alternatives)): ?>
    <div id="docs-api-alternatives" class="uk-margin-small-bottom">
      <?php print $alternatives; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($documentation)): ?>
    <div id="docs-api-documentation" class="uk-margin-bottom">
      <?php print $documentation ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($see)): ?>
    <div id="docs-api-see-also" class="uk-margin-bottom">
      <a href="#see-also" class="uk-link-muted docs-link-anchor">
        <h3 id="see-also" class="uk-panel-title"><?php print t('See also') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <ul class="uk-list">
        <?php print $see ?>
      </ul>
    </div>
  <?php endif; ?>

  <?php if (!empty($related_topics)): ?>
    <div id="docs-api-related-topics" class="uk-margin-bottom">
      <a href="#related-topics" class="uk-link-muted docs-link-anchor">
        <h3 id="related-topics"><?php print t('Related topics') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $related_topics ?>
    </div>
  <?php endif; ?>

  <?php if (isset($defined)): ?>
    <div id="docs-api-file" class="uk-margin-bottom">
      <a href="#file" class="uk-link-muted docs-link-anchor">
        <h3 id="file"><?php print t('File'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $defined; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($objects)): ?>
    <div class="docs-api-objects" class="uk-margin-bottom">
      <?php print $objects; ?>
    </div>
  <?php endif; ?>
</div>
