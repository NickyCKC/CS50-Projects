# Generated by Django 4.0.3 on 2022-09-03 13:07

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0010_rename_categoryname_category_category_name'),
    ]

    operations = [
        migrations.RenameField(
            model_name='listing',
            old_name='imageURL',
            new_name='image_url',
        ),
    ]
