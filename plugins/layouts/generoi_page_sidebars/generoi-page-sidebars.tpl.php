<div role="document" class="">
  <a id="top"></a>

  <?php if (!empty($content['header']) || !empty($content['navigation'])): ?>
    <header role="banner">
      <?php if (!empty($content['header'])): ?>
        <div class="l-header clearfix">
          <?php print render($content['header']); ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($content['navigation'])): ?>
        <nav class="l-navigation" role="navigation">
          <?php print render($content['navigation']); ?>
        </nav>
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <?php if (!empty($content['featured'])): ?>
    <section class="l-featured row">
      <div class="large-12 columns">
        <?php print render($content['featured']); ?>
      </div>
    </section>
  <?php endif; ?>

  <main role="main" class="row">
    <div class="main columns l-main">
      <?php if (!empty($content['highlighted'])): ?>
        <div class="highlight panel callout">
          <?php print render($content['highlighted']); ?>
        </div>
      <?php endif; ?>

      <a id="main-content"></a>

      <?php print render($content['content_above']); ?>
      <?php print render($content['content']); ?>
      <?php print render($content['content_below']); ?>
    </div>

    <?php if (!empty($content['sidebar_first'])): ?>
      <aside role="complementary" class="l-sidebar-first columns sidebar">
        <?php print render($content['sidebar_first']); ?>
      </aside>
    <?php endif; ?>

    <?php if (!empty($content['sidebar_second'])): ?>
      <aside role="complementary" class="l-sidebar-second columns sidebar">
        <?php print render($content['sidebar_second']); ?>
      </aside>
    <?php endif; ?>
  </main>

  <?php if (!empty($content['footer'])): ?>
    <footer class="l-footer panel row" role="contentinfo">
      <?php print render($content['footer']); ?>
    </footer>
  <?php endif; ?>
</div>
