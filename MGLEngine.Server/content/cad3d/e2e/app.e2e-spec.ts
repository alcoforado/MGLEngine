import { Cad3dPage } from './app.po';

describe('cad3d App', function() {
  let page: Cad3dPage;

  beforeEach(() => {
    page = new Cad3dPage();
  });

  it('should display message saying app works', () => {
    page.navigateTo();
    expect(page.getParagraphText()).toEqual('app works!');
  });
});
