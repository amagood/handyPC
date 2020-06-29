class Server {
  constructor(baseUrl) {
    this._baseUrl = baseUrl.toString() || '';
  }

  setBaseUrl(baseUrl) {
    this._baseUrl = baseUrl;
  }

  getBaseUrl() {
    return this._baseUrl
  }

  async getAllCategory() {
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/getAllCategory`));
    } catch (e) {
      console.error(`API getAllCategory() error: ${e.message}`);
    }
  }

  async getCategory(categoryId) {
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/getCategory/${categoryId}`));
    } catch (e) {
      console.error(`API getCategory(${categoryId}) error: ${e.message}`);
    }
  }

  async getProduct(productId) {
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/getProduct/${productId}`));
    } catch (e) {
      console.error(`API getProduct(${productId}) error: ${e.message}`);
    }
  }

  async getProductDetails(productId) {
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/getProductDetails/${productId}`));
    } catch (e) {
      console.error(`API getProductDetails(${productId}) error: ${e.message}`);
    }
  }

  async getEvaluation(productId) {
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/getEvaluation/${productId}`));
    } catch (e) {
      console.error(`API getEvaluation(${productId}) error: ${e.message}`);
    }
  }

  async createEvaluation(productIds) {
    const requestData = { ID: productIds };
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/createEvaluation`, 'POST', requestData));
    } catch (e) {
      console.error(`API createEvaluation(${productIds}) error: ${e.message}`);
    }
  }

  async deleteEvaluation(evaluationId) {
    const requestData = { ID: evaluationId };
    try {
      return this._handleResponse(await this._httpRequest(`${this._baseUrl}/deleteEvaluation`, 'POST', requestData));
    } catch (e) {
      console.error(`API deleteEvaluation(${productId}) error: ${e.message}`);
    }
  }

  async _httpRequest(url, method='GET', data=null) {
    return new Promise((resolve, reject) => {
      const xhr = new XMLHttpRequest();
      xhr.open(method, url, true); // syncronous request
      if (data === null) {
        xhr.send(null);
      } else {
        xhr.setRequestHeader('Content-Type', 'application/json');
        xhr.send(JSON.stringify(data));
      }

      xhr.onreadystatechange = () => {
        if (xhr.readyState != 4)
          return;
    
        if (xhr.status === 200)
          resolve(JSON.parse(xhr.responseText));
        else
          reject(new Error(`URL: '${url}'\nserver responded with ${xhr.status} ${xhr.statusText}.`));
      }
    });
  }

  _handleResponse(response) {
    if (!response)
      throw new Error(`response is empty`);
    
    if (response.statusCode !== 200)
      throw new Error(`server status is ${response.statusCode}\n`);
    
    const data = JSON.parse(response.dataString);

    if (data.status !== 200)
      throw new Error(`API ${data.status} error: ${data.error}`);
    
    return data;
  }
}

class Controller {
  constructor(server) {
    this._server = server;
    this._dom = {};
    this._data = [];
    this._evaluateList = [];
    this.fetchDomElement();
  }

  fetchDomElement() {
    this._dom = {
      categoryList: document.querySelector('#category-list'),
      categoryViewer: document.querySelector('#category-viewer'),
      productViewer: document.querySelector('#product-viewer'),
      evaluationBlock: document.querySelector('#evaluate-block')
    }
    const addEvaluateProductButton = this._dom.productViewer.querySelector('.add-evaluate-product-button');
    addEvaluateProductButton.addEventListener('click', () => { this.changeEvaluateProductNumber(parseInt(addEvaluateProductButton.dataset.productId, 10), 1) });
    this._dom.evaluationBlock.querySelector('.show-evaluation-button').addEventListener('click', () => { this.showEvaluation(); });
    this._dom.evaluationBlock.querySelector('.create-evaluation-button').addEventListener('click', () => { this.createEvaluation(); });
    this._dom.evaluationBlock.querySelector('.delete-evaluation-button').addEventListener('click', () => { this.deleteEvaluation(); });
    this._dom.evaluationBlock.querySelector('.evaluation-id').addEventListener('change', () => { this.handleEvaluationIdChange(); });
    this._dom.evaluationBlock.querySelector('.evaluation-id').addEventListener('input', () => { this.handleEvaluationIdChange(); });
    this._dom.evaluationBlock.querySelector('.evaluation-id').addEventListener('keydown', e => {
      if (e.key === 'Enter' && !this._dom.evaluationBlock.querySelector('.show-evaluation-button').classList.contains('hide'))
        this.showEvaluation();
    });
    this.handleEvaluationIdChange();
  }

  async update() {
    await this.updateData();
    this.clearView();
    this.updateView();
  }

  async updateData() {
    const categoryIds = (await this._server.getAllCategory()).ID;
    const categories = [];
    const products = [];

    // get categories
    for (const categoryId of categoryIds) {
      const category = {
        ...(await this._server.getCategory(categoryId)),
      };
      
      // get products
      for (const productId of category.AllProductID) {
        const product = {
          categoryId,
          ...(await this._server.getProduct(productId)),
          details: (await this._server.getProductDetails(productId))
        };
        ['Product_ID', 'status', 'timestamp'].forEach(key => { product.details[key] = undefined; })
        product.Watt = parseFloat(product.Watt);
        products.push(product);
      }

      categories.push(category);
    }

    this._data = {
      categories,
      products
    };
  }

  async showEvaluation() {
    const evaluationId = parseInt(this._dom.evaluationBlock.querySelector('.evaluation-id').value, 10);
    this._evaluateList = (await this._server.getEvaluation(evaluationId)).ID;
    this.drawEvaluation();
  }

  async createEvaluation() {
    const evaluationId = (await this._server.createEvaluation(this._evaluateList)).ID;
    this._dom.evaluationBlock.querySelector('.evaluation-id').value = evaluationId;
    this.handleEvaluationIdChange();
  }

  async deleteEvaluation() {
    const evaluationId = parseInt(this._dom.evaluationBlock.querySelector('.evaluation-id').value, 10);
    await this._server.deleteEvaluation(evaluationId);
    this._dom.evaluationBlock.querySelector('.evaluation-id').value = '';
    this.handleEvaluationIdChange();
  }

  handleEvaluationIdChange() {
    const evaluationId = parseInt(this._dom.evaluationBlock.querySelector('.evaluation-id').value, 10);
    if (Number.isNaN(evaluationId)) {
      this._dom.evaluationBlock.querySelector('.create-evaluation-button').classList.remove('hide');
      this._dom.evaluationBlock.querySelector('.show-evaluation-button').classList.add('hide');
      this._dom.evaluationBlock.querySelector('.delete-evaluation-button').classList.add('hide');
    } else {
      this._dom.evaluationBlock.querySelector('.create-evaluation-button').classList.add('hide');
      this._dom.evaluationBlock.querySelector('.show-evaluation-button').classList.remove('hide');
      this._dom.evaluationBlock.querySelector('.delete-evaluation-button').classList.remove('hide');
    }
  }

  clearView() {
    this._dom.categoryList.innerHTML = '';
    this._dom.categoryViewer.classList.add('hide');
    this._dom.productViewer.classList.add('hide');
  }

  updateView() {
    this.drawCategoryList();
    this.drawEvaluation();
  }

  checkCategory(categoryId) {
    this.drawCategoryViewer(categoryId);
  }

  checkProduct(productId) {
    this.drawProductViewer(productId);
  }

  changeEvaluateProductNumber(productId, num) {
    if (num >= 0) {
      for (let i = 0; i < num; ++i)
        this._evaluateList.push(productId);
    } else {
      for (let i = 0; i > num; --i) {
        const index = this._evaluateList.indexOf(productId);
        if (index < 0)
          break;
        this._evaluateList.splice(index, 1);
      }
    }
    this._evaluateList = this._evaluateList.sort();
    this._dom.evaluationBlock.querySelector('.evaluation-id').value = '';
    this.handleEvaluationIdChange();
    this.drawEvaluation();
  }

  drawCategoryList() {
    this._dom.categoryList.innerHTML = '';
    // draw category list
    for (const category of this._data.categories) {
      const item = document.createElement('li');
      item.innerHTML = category.Name;
      item.classList.add('clickable');
      item.dataset.categoryId = category.ID;
      item.addEventListener('click', () => { this.checkCategory(category.ID) });
      this._dom.categoryList.appendChild(item);
    }
  }

  drawCategoryViewer(categoryId) {
    for (const child of this._dom.categoryList.children) {
      if (parseInt(child.dataset.categoryId, 10) === categoryId)
        child.classList.add('selected');
      else
        child.classList.remove('selected');
    }
    
    this._dom.productViewer.classList.add('hide');

    const category = this._data.categories.find(category => category.ID === categoryId);
    const categoryViewer = this._dom.categoryViewer;
    categoryViewer.classList.remove('hide');

    categoryViewer.querySelector('.category-name').innerHTML = category.Name;
    categoryViewer.querySelector('.product-count').innerHTML = category.AllProductID.length;
    categoryViewer.querySelector('.category-description').innerHTML = category.Description;

    const productList = categoryViewer.querySelector('.product-table tbody');
    productList.innerHTML = '';

    for (const productId of category.AllProductID) {
      const product = this._data.products.find(item => item.ID === productId);
      const tr = document.createElement('tr');
      productList.appendChild(tr);
      tr.classList.add('clickable');
      tr.dataset.productId = productId;

      const productName = document.createElement('td');
      productName.innerHTML = product.Name;
      tr.appendChild(productName);

      const productPrice = document.createElement('td');
      productPrice.innerHTML = product.Price;
      tr.appendChild(productPrice);

      tr.addEventListener('click', () => { this.checkProduct(productId); });
    }
  }

  drawProductViewer(productId) {
    [...this._dom.categoryList.children].forEach(category => category.classList.remove('selected'));
    const productViewer = this._dom.productViewer;
    this._dom.categoryViewer.classList.add('hide');
    productViewer.classList.remove('hide');
    
    const product = this._data.products.find(item => item.ID === productId);

    productViewer.querySelector('.add-evaluate-product-button').dataset.productId = productId;
    productViewer.querySelector('.product-name').innerHTML = product.Name;
    productViewer.querySelector('.product-category').innerHTML = this._data.categories.find(category => category.ID === product.categoryId).Name;
    productViewer.querySelector('.product-price').innerHTML = product.Price;

    if (product.Discount) {
      productViewer.querySelector('.product-discount').parentNode.classList.remove('hide');
      productViewer.querySelector('.product-discount').innerHTML = product.Discount;
    } else {
      productViewer.querySelector('.product-discount').parentNode.classList.add('hide');
    }
    
    if (product.Picture) {
      productViewer.querySelector('.product-image').classList.remove('hide');
      productViewer.querySelector('.product-image').src = '';
      productViewer.querySelector('.product-image').src = product.Picture;
    } else {
      productViewer.querySelector('.product-image').classList.add('hide');
    }

    if (product.Description) {
      productViewer.querySelector('.product-description').parentNode.classList.remove('hide');
      productViewer.querySelector('.product-description').innerHTML = product.Description;
    } else {
      productViewer.querySelector('.product-description').parentNode.classList.add('hide');
    }

    if (product.Watt) {
      productViewer.querySelector('.product-wattage').parentNode.classList.remove('hide');
      productViewer.querySelector('.product-wattage').innerHTML = product.Watt;
    } else {
      productViewer.querySelector('.product-wattage').parentNode.classList.add('hide');
    }

    if (product.Discussion) {
      productViewer.querySelector('.product-discussion').classList.remove('hide');
      productViewer.querySelector('.product-discussion').href = product.Discussion;
    } else {
      productViewer.querySelector('.product-discussion').classList.add('hide');
    }

    const productDetails = productViewer.querySelector('.product-details');
    productDetails.innerHTML = '';
    for (const attribute in product.details) {
      if (product.details[attribute] !== undefined && product.details[attribute] !== null) {
        if (productDetails.childNodes.length > 0)
          productDetails.appendChild(document.createElement('br'));
        productDetails.appendChild(document.createTextNode(`${attribute}: ${product.details[attribute]}`));
      }
    }
  }

  drawEvaluation() {
    const evaluationBlock = this._dom.evaluationBlock;
    const evaluateList = evaluationBlock.querySelector('.evaluate-list');
    evaluateList.innerHTML = '';
    const templateDom = evaluationBlock.querySelector('.evaluate-item-template');

    const evaluateIds = [...(new Set(this._evaluateList))];

    // draw product list
    for (const productId of evaluateIds) {
      const numProducts = this._evaluateList.reduce((acc, cur) => (acc + (cur === productId ? 1 : 0)), 0);
      const product = this._data.products.find(product => product.ID === productId);
      const itemDom = templateDom.cloneNode(true);
      evaluateList.appendChild(itemDom);
      itemDom.classList.remove('hide');
      itemDom.querySelector('.product-name').innerHTML = product.Name;
      itemDom.querySelector('.product-price').innerHTML = product.Price;
      
      if (product.Picture) {
        itemDom.querySelector('.product-image').src = product.Picture;
      } else {
        itemDom.querySelector('.product-image').classList.add('hide');
      }

      if (product.Description) {
        itemDom.querySelector('.product-description').innerHTML = product.Description;
      } else {
        itemDom.querySelector('.product-description').innerHTML = product.Description = '';
      }

      itemDom.querySelector('.product-num').innerHTML = numProducts;
      itemDom.querySelector('.product-inc').addEventListener('click', () => {this.changeEvaluateProductNumber(productId, 1)});
      itemDom.querySelector('.product-dec').addEventListener('click', () => {this.changeEvaluateProductNumber(productId, -1)});
      itemDom.querySelector('.product-text').addEventListener('click', () => { this.drawProductViewer(productId); });
    }

    // draw summary
    let totalPrice = 0;
    let totalWattage = 0;
    this._evaluateList.forEach(productId => {
      const product = this._data.products.find(p => p.ID === productId);
      totalPrice += product.Price;
      if (this._evaluateList.length > 1)
        totalPrice -= product.Discount;
      totalWattage += product.Watt;
    });
    evaluationBlock.querySelector('.total-price').innerHTML = totalPrice;
    evaluationBlock.querySelector('.total-wattage').innerHTML = totalWattage;
  }
}

async function init() {
  const server = new Server('/api');
  const controller = new Controller(server);
  controller.update();
  window.server = server;
  window.controller = controller;
}

window.addEventListener('load', init);
