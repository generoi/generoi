<div <?php !empty($css_id) ? print 'id="' . $css_id . '"' : ''; ?>>
  <?php if (!empty($content['top'])): ?>
    <div class="row">
      <?php print $content['top']; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($content['left']) || !empty($content['right'])): ?>
  <div class="row">
    <?php print $content['left']; ?>
    <?php print $content['right']; ?>
  </div>
  <?php endif; ?>
  <?php if (!empty($content['bottom'])): ?>
    <div class="row">
      <?php print $content['bottom']; ?>
    </div>
  <?php endif; ?>
</div>
