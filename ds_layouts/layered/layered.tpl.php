<?php

/**
 * @file
 * Display Suite layered layout.
 */
?>
<<?php print $layout_wrapper; print $layout_attributes; ?> class="layered-wrapper <?php print $classes;?>">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if ($header): ?>
    <<?php print $header_wrapper ?> class="layered-header <?php print $header_classes; ?>">
      <?php print $header; ?>
    </<?php print $header_wrapper ?>>
  <?php endif; ?>

  <?php if ($background || $foreground): ?>
    <div class="layered-layer">
    <?php if ($background): ?>
      <<?php print $background_wrapper ?> class="layered-background <?php print $background_classes; ?>">
        <?php print $background; ?>
      </<?php print $background_wrapper ?>>
    <?php endif; ?>

    <?php if ($foreground): ?>
      <<?php print $foreground_wrapper ?> class="layered-foreground <?php print $foreground_classes; ?>">
        <div class="center-wrapper"><div class="center-content">
          <?php print $foreground; ?>
        </div></div>
      </<?php print $foreground_wrapper ?>>
    <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($footer): ?>
    <<?php print $footer_wrapper ?> class="layered-footer <?php print $footer_classes; ?>">
      <?php print $footer; ?>
    </<?php print $footer_wrapper ?>>
  <?php endif; ?>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
