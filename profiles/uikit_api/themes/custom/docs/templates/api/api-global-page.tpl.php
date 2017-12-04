<?php

/**
 * @file
 * Displays an API page for a global variable.
 *
 * Available variables:
 * - $alternatives: List of alternate versions (branches) of this global.
 * - $documentation: Documentation from the comment header of the global.
 * - $see: See also documentation.
 * - $deprecated: Deprecated documentation.
 * - $namespace: Name of the namespace for this function, if any.
 * - $defined: HTML reference to file that defines this global.
 * - $code: HTML-formatted declaration of this global.
 * - $related_topics: List of related groups/topics.
 * - $branch: Object with information about the branch.
 * - $object: Object with information about the global.
 *
 * Available variables in the $branch object:
 * - $branch->project: The machine name of the branch.
 * - $branch->title: A proper title for the branch.
 * - $branch->directories: The local included directories.
 * - $branch->excluded_directories: The local excluded directories.
 *
 * Available variables in the $object object:
 * - $object->title: Display name.
 * - $object->related_topics: Related information about the function.
 * - $object->object_type: For this template it will be 'global'.
 * - $object->branch_id: An identifier for the branch.
 * - $object->file_name: The path to the file in the source.
 * - $object->summary: A one-line summary of the object.
 * - $object->code: Escaped source code.
 * - $object->see: HTML index of additional references.
 *
 * @see api_preprocess_api_object_page()
 *
 * @ingroup uikit_themeable
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

  <?php if (!empty($deprecated)): ?>
    <div class="docs-api-deprecated" class="uk-alert uk-alert-warning uk-margin-bottom">
      <a href="#deprecated" class="uk-link-muted docs-link-anchor">
        <h3 id="deprecated"><?php print t('Deprecated') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $deprecated ?>
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

  <div id="docs-api-file" class="uk-margin-bottom">
    <a href="#file" class="uk-link-muted docs-link-anchor">
      <h3 id="file"><?php print t('File'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
    </a>
    <?php print $defined; ?>

    <?php if ($namespace): ?>
      <div id="docs-api-namespace" class="uk-margin-bottom">
        <a href="#namespace" class="uk-link-muted docs-link-anchor">
          <h3 id="namespace"><?php print t('Namespace'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
        </a>
        <?php print $namespace; ?>
      </div>
    <?php endif; ?>
  </div>

  <div id="docs-api-code" class="uk-margin-bottom">
    <a href="#code" class="uk-link-muted docs-link-anchor">
      <h3 id="code"><?php print t('Code'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
    </a>
    <?php print $code; ?>
  </div>
</div>
